/**
 * @file pre.js
 * @brief Web interface bridge for Minesweeper WASM implementation
 * @author ayrto
 * @date 2025
 *
 * This module provides the JavaScript bridge between the web UI and the
 * Emscripten-compiled C++ minesweeper game! It handles user input, board
 * rendering with color styling, and status synchronization.
 */

var Module = Module || {};

/**
 * @brief Debug hook for Emscripten runtime errors
 * @param {string} msg Error message from the WASM runtime
 */
Module.onAbort = function (msg) {
  console.error("Module.onAbort:", msg);
  try {
    console.error(new Error("Stack").stack);
  } catch (e) {}
};

(function () {
  // ===================================================================
  // * DOM Element References
  // ===================================================================
  var inputEl, outputEl, formEl;
  var colsEl, rowsEl, startBtn; // removed resetBtn
  var stSize, stMines, stFlags, stRevealed, stState;

  // ===================================================================
  // * State Management
  // ===================================================================
  var runtimeReady = false; ///< WebAssembly runtime initialization status
  var gameInitialized = false; ///< Game instance creation status
  var lastGameState = -1; ///< Track last known game state to detect transitions

  // iOS-like shake animation injection & trigger
  function triggerShake() {
    const cls = "ios-shake";
    // Inject keyframes & class style only once
    if (!document.getElementById("shake-style")) {
      const style = document.createElement("style");
      style.id = "shake-style";
      style.textContent = `@keyframes ios-shake {\n  0% { transform: translateX(0); }\n  10% { transform: translateX(-10px); }\n  20% { transform: translateX(8px); }\n  30% { transform: translateX(-8px); }\n  40% { transform: translateX(6px); }\n  50% { transform: translateX(-6px); }\n  60% { transform: translateX(4px); }\n  70% { transform: translateX(-4px); }\n  80% { transform: translateX(2px); }\n  90% { transform: translateX(-2px); }\n  100% { transform: translateX(0); }\n}\nbody.${cls} { animation: ios-shake 0.6s cubic-bezier(.36,.07,.19,.97); }`;
      document.head.appendChild(style);
    }
    // Restart animation: remove then re-add class
    document.body.classList.remove(cls);
    // Force reflow to allow re-trigger
    void document.body.offsetWidth; // reflow hack
    document.body.classList.add(cls);
    // Clean up class after animation ends
    setTimeout(() => document.body.classList.remove(cls), 650);
  }

  // ===================================================================
  // * DOM Element Management
  // ===================================================================

  /**
   * @brief Ensures all DOM element references are cached and event handlers attached
   *
   * This function initializes element references using getElementById, attaches
   * event listeners for user interactions, and sets up the Module.clearOutput
   * function for terminal clearing functionality.
   */
  function ensureElements() {
    // Cache DOM element references
    if (!inputEl) inputEl = document.getElementById("input");
    if (!outputEl) outputEl = document.getElementById("output");
    if (!formEl) formEl = document.getElementById("input-form");
    if (!colsEl) colsEl = document.getElementById("cols");
    if (!rowsEl) rowsEl = document.getElementById("rows");
    if (!startBtn) startBtn = document.getElementById("start");
    // removed: resetBtn reference
    if (!stSize) stSize = document.getElementById("st-size");
    if (!stMines) stMines = document.getElementById("st-mines");
    if (!stFlags) stFlags = document.getElementById("st-flags");
    if (!stRevealed) stRevealed = document.getElementById("st-revealed");
    if (!stState) stState = document.getElementById("st-state");

    setupOutputCleaning();
    setupFormHandler();
    setupButtonHandlers();
    setupInitialFocus();
  }

  /**
   * @brief Sets up the terminal output clearing functionality
   */
  function setupOutputCleaning() {
    Module.clearOutput = function () {
      if (!outputEl) ensureElements();
      if (outputEl) {
        outputEl.innerHTML = "";
        outputEl.scrollTop = 0;
      }
    };
  }

  /**
   * @brief Configures the form submission handler for move input
   */
  function setupFormHandler() {
    if (formEl && inputEl && !formEl._hasEvent) {
      formEl.addEventListener("submit", handleMoveSubmission);
      formEl._hasEvent = true;
    }
  }

  /**
   * @brief Configures event handlers for game control buttons
   */
  function setupButtonHandlers() {
    if (startBtn && !startBtn._hasEvent) {
      startBtn.addEventListener("click", handleGameStart);
      startBtn._hasEvent = true;
    }
  }

  /**
   * @brief Sets initial focus to the input field
   */
  function setupInitialFocus() {
    if (inputEl) {
      try {
        inputEl.focus();
      } catch (e) {}
    }
  }

  // ===================================================================
  // * Event Handlers
  // ===================================================================

  /**
   * @brief Handles form submission for player moves
   * @param {Event} e The form submission event
   */
  function handleMoveSubmission(e) {
    e.preventDefault();
    var raw = inputEl.value || "";
    var move = raw.trim();
    inputEl.value = "";

    if (!runtimeReady) {
      writeTo(outputEl, "[Loading WASM... try again]\n");
      return;
    }

    if (!gameInitialized) {
      writeTo(outputEl, "Start the game first using the controls above.\n");
      return;
    }

    try {
      Module.ccall("js_submit", "void", ["string"], [move]);
      updateStatus();
    } catch (err) {
      console.error("Error calling js_submit:", err);
    }
  }

  /**
   * @brief Handles game initialization with user-specified dimensions
   */
  function handleGameStart() {
    if (!runtimeReady) {
      writeTo(outputEl, "[Loading WASM... try again]\n");
      return;
    }

    var cols = parseInt(colsEl && colsEl.value ? colsEl.value : "10", 10);
    var rows = parseInt(rowsEl && rowsEl.value ? rowsEl.value : "10", 10);

    if (!(cols > 1 && rows > 1)) {
      writeTo(outputEl, "Invalid sizes. Use numbers greater than 1.\n");
      return;
    }

    try {
      if (Module.clearOutput) Module.clearOutput();
      Module.ccall("js_init", "void", ["number", "number"], [cols, rows]);
      gameInitialized = true;
      updateStatus();
      try {
        inputEl.focus();
      } catch (e) {}
    } catch (err) {
      console.error("Error calling js_init:", err);
    }
  }

  // ===================================================================
  // * Board Rendering and Color System
  // ===================================================================

  /**
   * @brief Escapes HTML special characters to prevent XSS
   * @param {string} s The input string to escape
   * @return {string} HTML-safe escaped string
   */
  function escapeHtml(s) {
    return s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
  }

  /**
   * @brief Detects if text contains minesweeper board content
   * @param {string} text The text to analyze
   * @return {boolean} True if text appears to contain board elements
   */
  function isBoardish(text) {
    // Detects game board patterns: numbers, cells, borders, labels
    return /(\s[1-8]\s)|(\s[#\*\|]\s)|(^(?:\s{1,2}\d{1,2})(?=\s*\|))|(\s[+\-]\s)/m.test(
      text
    );
  }

  /**
   * @brief Applies color styling to board text using CSS classes
   * @param {string} text The raw board text from C++
   * @return {string} HTML with colored spans for numbers and labels
   */
  function decorateBoardText(text) {
    var html = escapeHtml(text);

    // Color mine count numbers (1-8) with appropriate CSS classes
    html = html.replace(
      /(\s)([1-8])(\s)/g,
      '$1<span class="num$2">$2</span>$3'
    );

    // Color row labels on the left side of the board
    html = html.replace(
      /^(\s{1,})(\d{1,2})(?=\s*\|)/gm,
      function (_m, sp, num) {
        return sp + '<span class="label">' + num + "</span>";
      }
    );

    return html;
  }

  /**
   * @brief Writes text to the terminal output with optional board coloring
   * @param {HTMLElement} out The output element to write to
   * @param {string} text The text content to display
   */
  function writeTo(out, text) {
    if (!out) return;

    var html = isBoardish(text) ? decorateBoardText(text) : escapeHtml(text);
    out.innerHTML += html;
    out.scrollTop = out.scrollHeight;
  }

  // ===================================================================
  // * Game Status Management
  // ===================================================================

  /**
   * @brief Updates the status panel with current game statistics
   *
   * Retrieves game state from C++ via ccall and updates the DOM elements
   * displaying board size, mine count, flags placed, cells revealed, and game state.
   */
  function updateStatus() {
    if (!runtimeReady) return;

    try {
      var C = Module.ccall("js_status_columns", "number", [], []);
      var R = Module.ccall("js_status_rows", "number", [], []);
      var M = Module.ccall("js_status_mines_total", "number", [], []);
      var F = Module.ccall("js_status_flags", "number", [], []);
      var RV = Module.ccall("js_status_revealed", "number", [], []);
      var S = Module.ccall("js_status_state", "number", [], []);

      if (stSize) stSize.textContent = "Size: " + (C || 0) + "x" + (R || 0);
      if (stMines) stMines.textContent = "Mines: " + (M || 0);
      if (stFlags) stFlags.textContent = "Flags: " + (F || 0);
      if (stRevealed) stRevealed.textContent = "Revealed: " + (RV || 0);
      if (stState) {
        stState.textContent = "State: " + getGameStateText(S);
      }

      // Detect transition to Lost (2) and trigger shake only once per loss
      if (S === 2 && lastGameState !== 2) {
        triggerShake();
        inputEl.enabled = false;
      }
      lastGameState = S;
    } catch (e) {}
  }

  /**
   * @brief Converts numeric game state to human-readable text
   * @param {number} stateValue The numeric state from C++ GameState enum
   * @return {string} Localized game state description
   */
  function getGameStateText(stateValue) {
    switch (stateValue) {
      case 0:
        return "Playing";
      case 1:
        return "Won";
      case 2:
        return "Lost";
      default:
        return "—";
    }
  }

  // ===================================================================
  // * Emscripten Integration
  // ===================================================================

  /**
   * @brief Redirects Module.print output to the terminal display
   */
  Module.print = function () {
    var text = Array.from(arguments).join(" ") + "\n";
    if (!outputEl) ensureElements();
    writeTo(outputEl, text);
  };

  /**
   * @brief Redirects Module.printErr output to the terminal display
   */
  Module.printErr = function () {
    var text = Array.from(arguments).join(" ") + "\n";
    if (!outputEl) ensureElements();
    writeTo(outputEl, text);
  };

  /**
   * @brief Called when WebAssembly runtime is fully initialized
   *
   * Sets up the UI, displays welcome message, and prepares for user interaction.
   */
  Module.onRuntimeInitialized = function () {
    runtimeReady = true;
    ensureElements();

    writeTo(
      outputEl,
      "Press Start to create a board and begin playing.\n"
    );

    try {
      inputEl.focus();
    } catch (e) {}
  };

  // ===================================================================
  // * Initialization
  // ===================================================================

  // Early initialization of DOM references and focus
  ensureElements();
})();

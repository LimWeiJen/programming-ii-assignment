# SCFMS Video Demonstration Slides

This directory contains the presentation slide deck for the **Smart Campus Facility Maintenance System (SCFMS)** demonstration video (KIE1008 Programming II).

---

## 🖥️ How to Open & Present the Slides

1. **Open in any Web Browser:**
   - Double-click [`index.html`](index.html), or right-click `index.html` and choose **Open with -> Google Chrome / Microsoft Edge / Firefox**.
   - No internet connection or installation is required; all styles, diagrams, and scripts are 100% self-contained and run locally offline.

2. **Presentation Mode:**
   - Press **`F`** on your keyboard to enter Fullscreen mode.
   - Use your mouse or keyboard to step through the slides.

3. **Exporting as PDF / Handouts:**
   - In your browser, press **`Ctrl + P`** (Print).
   - Set Destination to **Save as PDF**, Layout to **Landscape**, and check **Background graphics**.
   - Each slide will cleanly format into an individual presentation page.

---

## ⌨️ Presentation Keyboard Shortcuts

| Key | Action |
| :--- | :--- |
| **`→`** / **`Space`** / **`PageDown`** | Next slide (or click right half of screen) |
| **`←`** / **`Backspace`** / **`PageUp`** | Previous slide (or click left half of screen) |
| **`Home`** | Jump to Slide 1 (Title) |
| **`End`** | Jump to Final Slide (Summary) |
| **`F`** | Toggle Fullscreen presentation mode |

---

## 📊 Slide Deck Structure (Zero Code, 100% Visual)

The presentation strictly translates [`VIDEO_DEMO_SLIDES_OUTLINE.md`](../VIDEO_DEMO_SLIDES_OUTLINE.md) into visual diagrams without code clutter:

| Slide # | Slide Title | Visual Focus |
| :---: | :--- | :--- |
| **1** | **Title Slide** | Project badge, architecture tags, and high-level system identity. |
| **2** | **System Architecture & Folders** | 3-Pillar visual layout: `classes/`, `data structures/`, and `data/`. |
| **3** | **OOP Class Hierarchy** | Visual inheritance tree: `Person` base class connecting to `FacilityManager`, `Technician`, and `Requester`, alongside the `Request` entity model. |
| **4** | **FIFO Pending Queue** | Interactive node diagram showing Enqueue at Tail (new tickets) -> Front Inspection -> Dequeue at Head (assignment). |
| **5** | **Custom Linked List Architecture** | `LinkedList` base container branching into 5 typed subclasses (`RequestLinkedList`, `TechnicianLinkedList`, etc.) and pointer-traversal mechanics (`curr = curr->getNext()`). |
| **6** | **DataManager & File Storage** | Bidirectional disk file serialization pipeline (`|` delimiter format) loading on startup and saving on shutdown. |
| **7** | **Program Flow (`main.cpp`)** | 5-step control lifecycle: Record Loading -> Role Select -> Authentication Gate -> Action Dispatch -> Graceful Exit. |
| **8** | **Maintenance Ticket Lifecycle** | End-to-end journey of a defect ticket: Requester submission -> FIFO Queue -> Manager dispatch -> Technician repair -> Permanent History audit log. |
| **9** | **Engineering Excellence Summary** | Highlighting compliance with rubric: zero STL vectors, custom pointer data structures, strict access guards, and 100% test pass rate. |


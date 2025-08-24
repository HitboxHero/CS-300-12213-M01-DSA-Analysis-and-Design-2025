# CS-300-12213-M01-DSA-Analysis-and-Design-2025

## About

This repository is part of my ongoing CS portfolio. It showcases my work in data structures and algorithms, with artifacts from two projects and a short reflection on how design choices affect performance and readability.

## Repository Contents

### Data Structure Analysis

**Summary:**
I compared three implementations for an ABC University course info system using a vector, a hash table, and a binary search tree. I analyzed worst-case Big-O for loading, prerequisite validation, printing an alphanumeric list, single-item lookups, and memory trade-offs to justify a structure choice. 

I laid out clear, side-by-side complexities and tied them back to concrete user actions like “print all courses” and “show one course’s prerequisites,” which made the trade-offs easy to see. 

I could have added a brief note on self-balancing trees and load-factor tuning. This would have rounded out the analysis and shown how average-case guarantees are maintained. 

The part I found the most challenging was keeping the analysis focused on worst case while still discussing realistic average behavior was tricky. I solved it by stating worst-case first and then noting practical conditions. 

**Tools and resources added to my network:**
- Big-O reference notes tied to real operations
- Structured comparison table for vector vs hash vs tree (kept for reuse) 

**Skills transferable to other projects:**
- Turning user actions into performance questions
- Arguing for a data structure with evidence, not preference

**How I made this project maintainable, readable, and adaptable:**
I wrote the analysis in small, named parts (load, validate, print, lookup, memory), so future readers can jump right to what they care about. 

---

### Course Planner

**Summary:**
I built a simple course planner that loads a CSV, stores courses in an unordered_map, prints all courses alphanumerically, and shows details for a single course with prerequisites. It normalizes keys, trims input, and gives a clean menu flow. 

I think I nailed the separation of concerns (i.e. loading, printing one course, printing all courses, and small helpers for trimming, normalizing, and CSV splitting). The sort step produces a predictable list for users. 

To make my work even better I could have added basic input validation messaging for malformed rows and a couple of unit tests around CSV parsing and key normalization to lock behavior. 

I found designing a minimal UI loop that does not get in the way to be the most challenging. I overcame this by keeping the menu tiny, pushing logic into functions, and normalizing inputs to avoid case surprises. 

**Tools and resources added to my network:**
unordered_map patterns for small CLI tools
A lightweight CSV line splitter for simple, unquoted inputs 

**Skills transferable to other projects:**
- Fast lookups with hashing and a sorted presentation layer
- Normalization routines that make user input predictable

**How I made this project maintainable, readable, and adaptable:**
Consistent naming, short helper functions, and a clear main loop. Sorting is isolated so I can replace the container later without touching the UI. 

---

Additional Reflections

### What was the problem you were solving in the projects for this course?
Build a small course planner and decide on the right data structure for its core actions: loading data, printing a sorted catalog, and showing one course with prerequisites. 

### How did you approach the problem? Consider why data structures are important to understand.
I mapped each user action to operations that matter for performance, then compared vector, hash, and tree on worst-case and average behavior. The choice affects both speed and code shape. 

### How did you overcome any roadblocks you encountered while going through the activities or project?
I kept functionality small and testable: normalize input, split CSV, load, then print. For analysis, I stuck to worst-case first and only then discussed averages to avoid confusion. 

### How has your work on this project expanded your approach to designing software and developing programs?
I start with the user’s most common action and design around that path. If the key output is a sorted list, I pick structures that make that cheap and predictable. 

### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
I lean on small helpers, normalized inputs, and clear boundaries between loading, data, and UI. That keeps changes local and makes it easy to swap out the container later. 

---

## Collaborators
For this assignment, I have added my instructor **SalemOthman** as a collaborator so they can review my portfolio work.

## Acknowledgments
Thanks to my instructor and classmates for their support and detailed feedback throughout the CS-300 course.

## Contact
For any questions or suggestions, please feel free to open an issue or contact me.

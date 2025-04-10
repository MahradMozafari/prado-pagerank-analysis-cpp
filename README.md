# Prado PageRank Analyzer

This project implements a PageRank-based analysis of artworks from the Prado Museum dataset using shared tags between artworks. It builds a graph of artworks and measures the relative importance of each node (artwork) based on connectivity. The project is implemented in C++.

---

## :scroll: Project Overview
- **Goal**: Identify the most "influential" artworks using PageRank based on shared work tags.
- **Dataset**: Prado dataset containing `picture_id` and `work_tag` fields.
- **Approach**:
  1. Load and clean the data.
  2. Parse the tags and construct a graph (either unweighted or weighted).
  3. Apply the PageRank algorithm.
  4. Analyze and visualize the top-ranked artworks.

---

## :gear: Features
- Efficient file loading and preprocessing
- Two graph construction strategies:
  - **Unweighted Graph**: Connects artworks that share tags.
  - **Weighted Graph**: Edges weighted by the number of shared tags.
- PageRank computation with and without weights
- Strategy comparison for better insight
- Visualization of the resulting artwork graph

---

## :file_folder: Project Structure
```
📁 prado-pagerank-analyzer/
├── src/
│   └── prado_pagerank.cpp       # Main C++ source file
├── data/
│   └── prado.csv                # Dataset with picture_id and work_tag
├── README.md                    # This file
├── diagram.pdf                  # Project explanation with diagrams (optional)
```

---

## :rocket: How to Run
### Requirements
- C++17 compiler (e.g., g++ or clang++)
- CMake (optional, for cross-platform builds)

### Compile
```bash
g++ -std=c++17 src/prado_pagerank.cpp -o prado_pagerank
```

### Run
```bash
./prado_pagerank
```

---

## :chart_with_upwards_trend: Diagrams
The `diagram.pdf` file provides:
- Architecture of the system
- Graph building strategies
- PageRank explanation with visual examples
- Comparison of strategies in table form

---

## :bulb: Future Improvements
- Integrate interactive graph visualization with a GUI
- Export top-ranked artworks to JSON/CSV
- Parallel computation of PageRank for performance

---

## :star: Credits
Developed by a Data Engineering & Algorithms enthusiast, inspired by real-world museum analytics.

---

## :page_facing_up: License
MIT License


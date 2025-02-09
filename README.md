[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=c%2B%2B)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) 

My small pet-project.🐶 <b>The project contains bugs</b>. For finding bugs and competent criticism I give a cookie 🍪.
Classic console snake. In the future I want to add support for the SFML library.
Navigate the snake using keys W, A, S, D collect food to grow, and avoid collisions!

## 🕹 Controls
- W – Move up
- S – Move down
- A – Move left
- D – Move right
- P - Pause

## Installation Guide
1. Clone the repository  
   ```sh
   git clone https://github.com/Ivan-Lysov/SnakeCpp
   ```
2. Go to the MySnake folder  
   ```sh
   cd SnakeCpp
   ```
3. Go to the branch `win-console-version`  
   ```sh
   git checkout win-console-version
   ```
4. Compile executable file
   ```sh
   g++ -o snake_game.exe main.cpp -Iinclude -static -O1
   ```
   4.1 Compilation options  
   **Optimization levels:**  
   - **O0** — no optimization (for debugging).    
   - **O1** — basic optimization.  
   - **O2** — aggressive speed optimization.  
   - **O3** — maximum optimization.  
   - **Os** — optimization by file size.
 5. Run the executable file
    ```sh
      ./snake_game.exe
    ```
## 📜 License
MIT License  
See [LICENSE](LICENSE) for details.

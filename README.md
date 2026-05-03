
 GitHub Repository
 https://github.com/TaiNguyen2004-sys/Power-Quality-Waveform-Analyser

 Compilation Steps
1. Open the project folder in CLion.
2. Let CMake reload the project configuration.
3. Build the project by selecting **Build > Build Project**.

### Running the Program
1. **Main Analysis:**
   - Select the `Power_Quality_waveform_analyser` target.
   - Run the program. It will read `power_quality_log.csv` and generate `results.txt`.
2. **Unit Testing:**
   - Select the `RunUnitTests` target.
   - Run the executable to view the validation results for RMS and Compliance logic in the console.

## Project Structure
- `main.c`: Entry point for the analysis workflow.
- `waveform.c/h`: Core mathematical functions (RMS, Peak-to-Peak, etc.).
- `io.c/h`: File handling for CSV input and text report output.
- `testmain.c`: Unit testing suite.
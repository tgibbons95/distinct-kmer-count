<div id="top"></div>
<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#output">Output</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
      </ul>
    </li>
    <li><a href="#license">License</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This project is meant to find the number of unique K-mers in the suffix tree using the BWT and Reverse BWT of a string. The output computed in this repo was found from a provided DNA segquence for the assignment.

Known implementation issues
* Issues finding the children of an internal node and decrementing the kmer count in constant time. The algorithm should still compute the value correctly, but is linear in finding the children. In the worst case, this algorithm will run O(n^2). With the provided input for this assignment, the sequence still ran quickly because it wasn't a worst case scenario.


<p align="right">(<a href="#top">back to top</a>)</p>

### Output

[Kmers 20-40](https://github.com/wustl-cse584/homework-3-problem-3-ThomasGibbonsIV/blob/main/output/output.txt)

<p align="right">(<a href="#top">back to top</a>)</p>

### Built With

* [CMake](https://cmake.org/)
* [C++](https://www.cplusplus.com/)
* [GoogleTest](https://github.com/google/googletest)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

This project requires at least C++14 because of calls to std::make_unique

### Installation

A few example installations are provided for compilers [clang](https://github.com/wustl-cse584/homework-3-problem-3-ThomasGibbonsIV/blob/main/build-clang.sh), [gcc](https://github.com/wustl-cse584/homework-3-problem-3-ThomasGibbonsIV/blob/main/build-gcc.sh), [minGW](https://github.com/wustl-cse584/homework-3-problem-3-ThomasGibbonsIV/blob/main/build-minGW.sh), and [msvc](https://github.com/wustl-cse584/homework-3-problem-3-ThomasGibbonsIV/blob/main/build-msvc.sh).

Running any of these scripts will create a build and install directory with a subdirectory with the chosen compiler. Things to known are that the implementation does use std::thread so some compilers (namely minGW) may need additional installed add-on libraries that do not come with the initial download of the compiler. The install should look like the following (example done with Windows)

* include
  * BurrowsWheelerTransform.h
  * EnumTree.h
  * SuffixArray.h
* lib
  * DistinctKmerLib.lib
* test
  * DistinctKmerTest.exe
  
### Usage

To run simply place the sequence file `human-seq.txt` in the same directory as the executable and then kick off the executable. If these files aren't included, then it will just run against smaller test case inputs.

./DistinctKmerTest.exe



<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Used [README-Template](https://github.com/othneildrew/Best-README-Template) to create this readme.
# Evolutionary-Algorithm-In-Flocking-Simulation

<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />

<div align="center">
  <a href="https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Evolutionary-Algorithm-In-Flocking-Simulation</h3>

  <p align="center">
        This project aims to develop a flocking simulation in the
virtual world using unreal engine4. To achieve the goal, an evolutionary algorithm is
used to produce the fittest individual in this virtual simulation based on survival time.
The explanation will focus on implementation of genetic algorithms since it is the
core to support this application running. Detailed alogrithm explanation will be take place at discussion section
    <br />
    <a href="https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation">View Demo</a>
    ·
    <a href="https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation/issues">Report Bug</a>
    ·
    <a href="https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#discussion">Discussion</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

![Product Name Screen Shot][product-screenshot]



<p align="right">(<a href="#top">back to top</a>)</p>



### Built With

* [![cpp][cpp]][cpp-url]
* [![unreal][unreal]][unreal-url]


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.

Unreal Engine 4.24.3
Visual Studio 2017(Recommended)

### Installation

1. Download [Visual Studio](https://visualstudio.microsoft.com/downloads/) and [Unreal Engine](https://www.epicgames.com/id/login?lang=en-US&noHostRedirect=true&redirectUrl=https%3A%2F%2Fstore.epicgames.com%2Fen-US%2Fdownload&client_id=875a3b57d3a640a6b7f9b4e883463ab4&prompt=pass_through)
2. Clone the repo
   ```sh
   git clone https://github.com/pt4300/Goal-Oriented-Action-Planning-Visualization-Project.git
   
3. Click Run

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Discussion -->
## Discussion

First of all, the evolution algorithm populates 100 boids in the virtual space with
random attributes to give diversion in the population base. The random initialization
is chosen over heuristic initialization because the population will have very similar
solutions and very little diversity if we choose the latter. With some experiment I
found the random initialization produces the most optimistic population compared to
heuristic. The population model used in this evolutionary algorithm is generational
where entire population is replaced by the new population by the end of iteration, the
reason for this is because it is difficult to determine the fitness of child with existing
parent as the fitness function is based on the survival time which only exist after
population is existed in virtual environment.

Secondly, the fitness function used in this evolution algorithm is purely based on the
survival time with debuffing on death methods. For predator kill the boids received a
50 percent deduction on their fitness value whereas wall collision gives 25 percent
deduction. This fitness allows an extremely fast computation time with adequate
measure on how fit a boid is in this virtual world.

Parent selection takes place after fitness is calculated, roulette wheel selection is
used here to determine the fitness value of each boid in the population. This includes
the killed boids since breeding takes place among all boids in the population rather
than only survivors. The roulette wheel algorithm first calculates the fitness sum of all
boids and then picks a random value from 0 to fitness sum as the fixed point. After
this, a for loop is carried out from the top of the boids array( this is sort in ascending
order before this loop), then adding a partial sum p until p < s. Then the body for
which P exceeds S will be chosen as the parent. There are also multiple other
methods to generate parents such as stochastic universal sampling, tournament
selection and rank selection. I choose the roulette wheel selection because it is best
fit to the context of this project, for example, rank selection supports negative fitness
values and is mostly used when the individuals element in the population have very
close fitness values. However, the fitness value of this evolutionary algorithm is the
survival time and it means neither advantage of the rank selection methodology. The
stochastic universal sampling provides multiple fixed points when choosing parents
which allows the algorithm to generate multiple parents each iteration. This also did
not fit our context very well since only two parents needed to generate two offsprings
so there is no need to generate more than two parents at once.
Furthermore the crossover operators use one point crossover with fixed crossover
point to generate the offspring DNA. The reason for choosing this method is that one
point crossover provides more efficient computation on generating new DNA for
offspring in a given time period. Multi-point crossover and uniform crossover
provides other solutions to crossover function, the result suggests that one point
crossover produces the best outcomes overall.

In addition to crossover, mutation is done through the random resetting to genes of
the offspring. This gives the offspring more diversity and so it can make the entire
population have a better chance of producing optimal solutions. There is also swap
mutation, bit flip mutation, scramble mutation and inversion mutation. However those
mutation operators do not fit into this evolutionary algorithm. First, bit flip mutation is
used for binary encoded evolutionary algorithms, but this algorithm is developed
using integer representation as each attribute is integer. Swap mutation is not
working since each gene has a different set of range, for example the avoidance
distance ranges from 10 to 200 whereas the perception radius can be ranged from
500 to 3000. Scramble and inversion mutation both apply mutation to a subset of
gene, this will produce results for incorrect range over each gene due to the same
reason for swap mutation. Therefore, random resetting is the only viable option to
produce mutation operations in this project.

The survival selections process replaces the entire existing population without
elitism. This process also doesn't not use aged selection. The reason to replace the
entire population instead of fitness-based selection or aged based selection is
because the newly generated offspring does not have age and fitness since the
fitness is equal to age. As a result, the elitism or aged selection will randomly wipe
out offspring that potentially can produce better results than their parents. Thus
elitism and aged based selection can not be properly carried out on this design.
The genotypes choosed to calculate the optimal solution respectively are speed, turn
rate, avoidance distance and perception distance. These four attributes from each
boid can determine how long a boid survived in this virtual land. First of all, the
speed of boids can determine whether the boids are able to run away from its
predator when they are targeted. With low speed, the body will easily kill and receive
a low fitness as predator kill results in a 50 percent debuff. For the turn rate, these
genotypes determine how fast a boid will turn around before it hit the moving
asteroid. This higher the value are, a greater chance the boids can avoid hitting the
asteroid, and it improves the survival time as the crashing causes 25 percent
deduction in fitness value. Avoidance distance applies to both asteroid and predator,
this value determines how far a boid can spot a nearby threat and produces an
corresponding avoidance vector to flee away from the threat point. Boids with low
avoidance distance are commonly more likely to be killed compared to higher
avoidance distance from inspection. The last genotype is perception radius, this
value controls how far the boids can spot its neighbouring boid, it is different to the
avoidance distance as perception distance controls flocking behaviour of the boids.
This value plays an important role in generating optimal solutions to the results as
the behaviour of flocks determines how likely bodies will collide with the wall or be
killed by predators.

<p align="right">(<a href="#top">back to top</a>)</p>





<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Yuting Yu - pt4300@hotmail.com

Project Link: [https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation](https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation)

<p align="right">(<a href="#top">back to top</a>)</p>






<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation.svg?style=for-the-badge
[contributors-url]: https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation.svg?style=for-the-badge
[forks-url]: https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation/network/members
[stars-shield]: https://img.shields.io/github/stars/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation.svg?style=for-the-badge
[stars-url]: https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation/stargazers
[issues-shield]: https://img.shields.io/github/issues/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation.svg?style=for-the-badge
[issues-url]: https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation/issues
[license-shield]: https://img.shields.io/github/license/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation.svg?style=for-the-badge
[license-url]: https://github.com/pt4300/Evolutionary-Algorithm-In-Flocking-Simulation/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/yuting-yu-5a34031b5
[product-screenshot]: images/initial.jpg
[cpp]: https://img.shields.io/badge/c++-000000?style=for-the-badge
[cpp-url]: https://nextjs.org/
[unreal]: https://img.shields.io/badge/unreal-20232A?style=for-the-badge
[unreal-url]: https://reactjs.org/
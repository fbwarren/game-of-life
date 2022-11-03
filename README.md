# game-of-life

This is a simple implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).  
To run it, clone this project and run `./frames.csh <imagename> <rule> <frames>`  
The image must be a [ppm](https://netpbm.sourceforge.net/doc/ppm.html) format file. There's some examples in `./testInputs`   
Here's how rule is defined, using the rule `0x1808` as an example:
<table>
  <tbody>
    <tr>
      <th>If a cell's state is...</th>
      <th colspan="9"> alive (1)</th>
      <th colspan="9"> dead (0)</th>
    </tr>
    <tr>
      <th>And the number of alive neighbors is...</th>
      <td>8</td>
      <td>7</td>
      <td>6</td>
      <td>5</td>
      <td>4</td>
      <td>3</td>
      <td>2</td>
      <td>1</td>
      <td>0</td>
      <td>8</td>
      <td>7</td>
      <td>6</td>
      <td>5</td>
      <td>4</td>
      <td>3</td>
      <td>2</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <th>Then the cell's next state is...</th>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>1</td>
      <td>1</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
      <td>1</td>
      <td>0</td>
      <td>0</td>
      <td>0</td>
    </tr>
    <tr>
      <th>Converting the 18 bits above to a hexadecimal number</th>
      <td colspan="18"><p align="center">0b00 0001 1000 0000 1000</p>
        <p align="center">0x1808</p></td>
      </tr>
  </tbody>
</table>

`<frames>` determines how many steps of the simulation you want to have in your ouput gif

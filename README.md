# Algorithms_and_Data_Structures_II

<div>
<h2 align="left">
  <a href="https://github.com/BoguslawBanas/Algorithms_and_Data_Structures_II/blob/main/Mrok.cpp">1. Mrok (Dark)</a>
</h2>
<p align="left">
	A simple exercise which the main point was to implement the Dijkstra's algorithm. We got the imput which represents the n amount of points on the 2-dimensional grid. We also get the start and the end point which we need to reach and output the minimal distance to do that. The formula to calculate the distance between two points is abs(p1.x-p2.x)&ltabs(p1.y-p2.y) ? abs(p1.x-p2.x) : abs(p1.y-p2.y). Due to the fact that our graph is a sparse one the best option is an adjacency list.
</p>

<h2 align="left">
  <a href="https://github.com/BoguslawBanas/Algorithms_and_Data_Structures_II/blob/main/fortel_krola2.cpp">2. Fortel Króla (The Queen's Gambit)</a>
</h2>
<p align="left">
	The main point in this one is to implement the Hopcorft-Karp algorithm, which is used to solve the maximum-cardinality matching problem. As the input we got a n size chessboard (matrix). Each field can have four types of pawn. Except "0", which cannot beat and be beaten, they are very similiar. Like in the previous exercise we've got a sparse graph. The result is the amount of pawns which are on the chessboard which left after the maximum amount of pawns were removed.
</p>

<h2 align="left">
  <a href="https://github.com/BoguslawBanas/Algorithms_and_Data_Structures_II/blob/main/izba_z_kart.cpp">3. Izba z kart (House of Cards)</a>
 </h2>
<p align="left">
  A rather simple exercise. At the beginning we get the n amount of numbers to put in a simple binary-search tree. Then we get two numbers which represent the boundaries. We have to trim our previously created BST and finally we have to find in that new set a pair of numbers with smallest difference between them or output "NIE ZNALEZIONO" ("NOT FOUND") if there isn't one.
</p>

<h2 align="left">
  <a href="https://github.com/BoguslawBanas/Algorithms_and_Data_Structures_II/blob/main/mizerni_slepcy.cpp">4. Mizerni ślepcy (Peaky Blinders)</a>
</h2>
<p align="left">
An exercise where we need to implement our own Red-Black Tree and Linked List. In the Red-Black Tree we have to implement an add operation and rotations in case if the tree become a degenerate one (there is no need to implement the delete operation). As an input we get n amount of strings to put at the end of out list and add the pointer to our map (RBT). Later we can have 3 types of operations. <br/>
  1. swap - we just get two strings in our list <br/>
  2. move - we get a string and a value (int) which represents where we need to move that string in list. <br/>
  3. add - we just add another string to our list and RBT. <br/>
  We use RBT to have the time complexity of O(log(n)) instead of O(n) to find string in our list.
</p>

<h2 align="left">
  <a href="https://github.com/BoguslawBanas/Algorithms_and_Data_Structures_II/blob/main/jenne.cpp">5. Jenne (Wednesday)</a>
</h2>
<p align="left">
The main goal here is to find out is a given pattern present in a text. At the beginning we get the pattern which contains only a few types of characters: <br/>
  '0' - represents a number <br/>
  'a' - represents a small character <br/>
  'A' - represents a capital character <br/>
  '.' - represents a few special characters (like point, comma, exclamation mark etc.) <br/>
  ' ' - represents a space <br/>
 Here to find the pattern we use Knuth-Morris-Pratt algorithm, so we create an addictional array[pattern.length()] and fill the cells using prefix funcion. Later we move to our main text. After checking if we didn't reach the end of the line, we convert a charcter like above and move forward. If there is a match, we output 'T' and finish our program, otherwise we output 'N'.
</p>
</div>

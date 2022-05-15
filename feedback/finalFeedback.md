## **Dev Log**
### Grade 
100
### Comments
Never missed a log so good work!

## **Presentation** 
### Content Grade
100
### Skills Grade
100
### Comments

Good breakdown of development details, good visuals, good split of content, and a reasonable walkthrough at the end. Great work!

Was a little bit of audio problems towards the end but it was still understandable.

## **Written Report**
### Grade
100
### Comments
You ended up implementing three algorithms in four different ways so above and beyond what a final project was required to have (arguably four algorithms too since DFS / Floyd / SCC / Pagerank can all be considered different). Excellent work! The written report was straight and to the point (although I would have liked a bit more concrete details in the test set. The generic description 'we compared our manual computed X with output Y' or 'we got the expected value' is good but doesn't really tell me anything. I have to look at the tests themselves to still work out what is happening.)

## **README** 
### Grade
100

### Comments
An outstanding README! Very well done labeling of where files are located and a figure does an excellent job overviewing the flow of the code itself. Your README is so good I had to brag about it to Carl and I'd like to use this as an example of exactly what to do in the future. 

## **Code** 
### Goals Grade
100

### Execution Grade
100

### Efficiency Grade
100

### Organization Grade
100

### Comments

An almost perfect project! Efficiencies largely line up, execution is clear and almost entirely correct, organization is well thought out and the code is reasonably readable. I ran into some problems with your PageRank algorithm, although since you technically completed three algorithms perfectly (DFS / SCC / SP), you haven't lost any points here. 

As for pagerank, it does work but only on a single SCC. Which is clearly by design but was not actually in the proposal and I would argue that that's technically not doing pagerank correctly. A lot of my personal tests (which have things like sinks or multiple SCC) weren't working -- obviously because they aren't being calculated at all. But again since this is sort of going above and beyond anyways (and you clearly spent a lot of time implementing alternative Pagerank strategies) its fine.

Misc Feedback:
I would have liked some additional comments in the test part of your code -- the dfs test set was particularly tough to get through since it used an unusual testing structure with unclear variables. It was easy enough to understand the tests themselves -- which was great -- but I had a harder time making sure the tests were working correctly. 

I also would suggest putting the results.md in the 'documents' directory but the README pointed right to it so it didnt matter. 

It was a very clever setup for outputting the results in full and then having a separate code base to process / parse! My only suggestion there is it was a bit odd that I had to zip my results directory to 'read' them (although it does it automatically which is nice). And it was a bit of a hassle to have to open another file when parsing my results. It might have been better from a design point of view to summarize the output in the final parse. For example, giving the string of visits as a vector or a distance calculation instead of three lines per node visited. 
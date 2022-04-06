### Grade
Not Yet Competent (70%)

Please resubmit! (As an apology for getting feedback to you late, I will not be giving you a grade penalty on this regrade attempt)

### Comments
Most of the proposal is well-written but there are a few major gaps / unclear details about the function input / output and their relationship to the dataset. To summarize: your Big Os are mostly wrong, the input to several functions dont make sense, and the dataset have some major ommissions. 

**Leading Question**
Finding the shortest path between two airports makes sense and clearly identifies both the dataset and the algorithms. The strongly connected component question does not make sense.

**Dataset**
The data format is well described with clear columns of interest, a reasonable data correction step, and some good data storage details. However the description of the data storage / processing needs improvement. Notably: 1) It is not clear how you plan to generate distances [there are multiple viable strategies here, although randomly assigning weights for 'check-ins' is not one of them]. 2) It is not clear if your data is directed or undirected. This is a major problem since your algorithms all require a directed dataset.

I would also encourage you to consider how you will handle disjoint subsets of the dataset -- an airport or set of airports which don't connect to the 'main' graph network may cause problems for your algorithms if not removed or accounted for. (It is of course your choice if you will remove it in data processing or account for it in the algorithm).

**Algorithm**
Floyd-Warshall is reasonably described and makes sense. (Just be sure your data is weighted directed!). The Big O here is also reasonable.

Your pagerank algorithm is interesting but doesn't match the data. As far as I am aware, there aren't duplicates in the flight dataset. So your dataet would just have a bunch of 'weight 1' edges would is a completely non-interesting pagerank setup. I'm not sure if there's much meaning behind a pagerank on distances, but at least it would be a more interesting (and straightforward setup). The big O for pagerank is also significantly off -- PageRank is a repeating calculation over nodes and edges but only for a fixed number of iterations (simple) or an unbounded number of iterations with a damping factor (more complex). In both cases, there is a much more straightforward Big O that is better than O(n^3). The memory footprint is fine though.

Your strongly connected component algorithm correctly recognizes that weights here don't matter which is good. However I don't understand at all how the bool check-in will have any relation to strongly connected components. This needs to be significantly re-written / explained and in general I would advise against making up some random value in the first place -- just use the actual dataset given or find a real-world dataset that matches what you are trying to do. You have also not concretely stated an algorithm for producing strongly connected components so when you resubmit your proposal please try to identify one to tighten your Big O numbers in that space. (The listed Big O here is also not reasonable, there are straightforward solutions which are much better than your proposed efficiency.)

Overall, note that Floyd-Warshall, strongly connected component, *AND DFS* (which is not one of your listed algorithms but should be) is a sufficient amount of work. [And yes it is fine that some of the strongly connected component algorithms will use DFS as long as I can separately run DFS directly as well as the strongly connected component algorithm. Also note that DFS should be run on a directed graph.]
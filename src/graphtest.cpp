/**
 * Copyright 2012 Alexandre Blondin Masse
 *
 * This file is part of the MFVS project.
 *
 * MFVS is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or any later version.

 * MFVS is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <algorithm>
#include <set>

#include <time.h>

#include "graph.h"

using namespace std;

int main() {
    Graph g(5);
    cout << "Adding vertices 0,1,2,3,4" << endl;
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    cout << "Adding edges (0,1), (1,2), (0,3), (2,0) and (2,2)" << endl;
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 0);
    g.addEdge(2, 2);
    g.print(true);
    cout << endl;
    
    cout << "Sources : ";
    vector<int> sources = g.sources();
    for (int i = 0; i < int(sources.size()); ++i) cout << sources[i] << " ";
    cout << endl;

    cout << "Sinks : ";
    vector<int> sinks = g.sinks();
    for (int i = 0; i < int(sinks.size()); ++i) cout << sinks[i] << " ";
    cout << endl;

    cout << "Loops : ";
    vector<int> loops = g.loops();
    for (int i = 0; i < int(loops.size()); ++i) cout << loops[i] << " ";
    cout << endl;

    for (set<int>::iterator it = g.vertices().begin(); it != g.vertices().end(); ++it) {
        cout << "Vertex " << *it << endl;
        cout << " Incoming neighbors : ";
        vector<int> incomingNeighbors = g.incomingNeighbors(*it);
        for (vector<int>::iterator jt = incomingNeighbors.begin(); jt != incomingNeighbors.end(); ++jt) {
            cout << *jt << " ";
        }
        cout << endl;
        cout << " Outgoing neighbors : ";
        vector<int> outgoingNeighbors = g.outgoingNeighbors(*it);
        for (vector<int>::iterator jt = outgoingNeighbors.begin(); jt != outgoingNeighbors.end(); ++jt) {
            cout << *jt << " ";
        }
        cout << endl;
    }

    cout << "Strongly connected components :" << endl;
    vector< vector<int> > sccs = g.stronglyConnectedComponents();
    for (int i = 0; i < int(sccs.size()); ++i) {
        cout << " #" << i << " : ";
        for (int j = 0; j < int(sccs[i].size()); ++j) {
            cout << sccs[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Now by number :" << endl;
    vector<int> vertexToSCC = g.vertexToStronglyConnectedComponentNumber();
    for (int i = 0; i < int(vertexToSCC.size()); ++i) {
        cout << i << " : " << vertexToSCC[i] << endl;
    }

    cout << "Deleting edge (0,3)" << endl;
    g.deleteEdge(0, 3);
    g.print(true);
    cout << endl;
    cout << "Deleting vertex 2" << endl;
    g.deleteVertex(2);
    g.print(true);
    cout << endl;
    cout << "Deleting vertices 1 and 4" << endl;
    vector<int> vertices;
    vertices.push_back(1);
    vertices.push_back(4);
    g.deleteVertices(vertices);
    g.print(true);
    cout << endl;

    cout << "Adding vertex 2" << endl; 
    g.addVertex(2);
    cout << "Adding edges (0,3), (2,0), (2,3) and (3,3)" << endl;
    g.addEdge(0, 3);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.print(true);
    cout << endl << endl;

    cout << "Applying IN0" << endl;
    vector<int> in0Vertices = g.in0();
    g.print(true);
    cout << endl;
    cout << " Vertices ";
    for (vector<int>::iterator it = in0Vertices.begin(); it != in0Vertices.end(); ++it)
        cout << *it << " ";
    cout << "have been removed." << endl;
    cout << endl;

    cout << "Applying LOOP" << endl;
    vector<int> loopVertices = g.loop();
    g.print(true);
    cout << endl;
    cout << " Vertices ";
    for (vector<int>::iterator it = loopVertices.begin(); it != loopVertices.end(); ++it)
        cout << *it << " ";
    cout << "have been removed." << endl;
    cout << endl;

    cout << "Refilling the graph";
    cout << "Adding vertices 1,2,3,4" << endl;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    cout << "Adding edges (0,1), (0,2), (1,1), (1,0), (2,3), (3,1), (3,4) and (4,2)" << endl;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 1);
    g.addEdge(1, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.addEdge(3, 4);
    g.addEdge(4, 2);
    g.print(true);
    cout << endl;
    cout << "Merging vertex 2" << endl;
    g.mergeVertex(2);
    g.print(true);
    cout << endl;

    cout << "Adding edge (3,0)" << endl;
    g.addEdge(3, 0);
    g.print(true);
    cout << endl;
    cout << "Applying IN1" << endl;
    cout << "Vertices ";
    vector<int> in1Vertices = g.in1();
    for (vector<int>::iterator it = in1Vertices.begin(); it != in1Vertices.end(); ++it)
        cout << *it << " ";
    cout << "have been merged." << endl;
    g.print(true);
    cout << endl;

    cout << endl << "Building a graph from a file" << endl;
    Graph h("graph6.txt", Graph::TYPE_ADJACENCY_LIST);
    h.print(true);
    cout << endl;

    cout << "Applying OUT1" << endl;
    cout << "Vertices ";
    vector<int> out1Vertices = h.out1();
    for (vector<int>::iterator it = out1Vertices.begin(); it != out1Vertices.end(); ++it)
        cout << *it << " ";
    cout << "have been merged." << endl;
    h.print(true);
    cout << endl;

    cout << endl << "Reloading the graph and adding some edges to it" << endl;
    Graph h2 = Graph("graph6.txt", Graph::TYPE_ADJACENCY_LIST);
    h2.addEdge(1, 3);
    cout << "Trying copy constructor" << endl;
    Graph h3(h2);
    h3.print(true);
    cout << endl;
    cout << "Deleting vertex in the copied graph" << endl;
    h3.deleteVertex(2);
    cout << "Priting the original graph" << endl;
    h2.print(true);
    cout << endl;
    cout << "And the copied one" << endl;
    h3.print(true);
    cout << endl;
    cout << "Seems to work !" << endl << endl;

    cout << "Continuing testing the graph" << endl;
    h3.print(true);
    cout << endl;
    cout << "Strongly connected components :" << endl;
    sccs = h3.stronglyConnectedComponents();
    for (int i = 0; i < int(sccs.size()); ++i) {
        cout << " #" << i << " : ";
        for (int j = 0; j < int(sccs[i].size()); ++j) {
            cout << sccs[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Edges : ";
    vector<Edge> allEdges = h3.edges();
    for (vector<Edge>::iterator it = allEdges.begin(); it != allEdges.end(); ++it) {
        cout << "(" << it->source << "," << it->target << ") ";
    }
    cout << endl;
    cout << "Acyclic edges : ";
    vector<Edge> acyclicEdges = h3.acyclicEdges();
    for (vector<Edge>::iterator it = acyclicEdges.begin(); it != acyclicEdges.end(); ++it) {
        cout << "(" << it->source << "," << it->target << ") ";
    }
    cout << endl;
    cout << "Pi-edges : ";
    vector<Edge> piEdges = h3.piEdges();
    for (vector<Edge>::iterator it = piEdges.begin(); it != piEdges.end(); ++it) {
        cout << "(" << it->source << "," << it->target << ") ";
    }
    cout << endl;
    cout << "Pseudo-acyclic edges : ";
    vector<Edge> pseudoAcyclicEdges = h3.pseudoAcyclicEdges();
    for (vector<Edge>::iterator it = pseudoAcyclicEdges.begin();
         it != pseudoAcyclicEdges.end(); ++it) {
        cout << "(" << it->source << "," << it->target << ") ";
    }
    cout << endl;
    cout << "Applying PIE" << endl;
    vector<Edge> pieEdges = h3.pie();
    cout << "Edges ";
    for (vector<Edge>::iterator it = pieEdges.begin(); it != pieEdges.end(); ++it) {
        cout << "(" << it->source << "," << it->target << ") ";
    }
    cout << "have been removed." << endl << endl;

    cout << "Reloading the graph" << endl;
    g = Graph("graph6.txt", Graph::TYPE_ADJACENCY_LIST);
    g.print(true);
    cout << endl;
    h = g.groundingKernel();
    cout << "Computing its grounding kernel" << endl;
    h.print(true);
    cout << endl << endl;

    cout << "Reloading the graph again and adding some edges" << endl;
    g = Graph("graph6.txt", Graph::TYPE_ADJACENCY_LIST);
    g.addEdge(1, 0);
    g.addEdge(5, 0);
    g.print(true);
    cout << endl;
    cout << "Pi-vertices : ";
    vector<int> piVertices = g.piVertices();
    for (vector<int>::iterator it = piVertices.begin(); it != piVertices.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Loading graph of Figure 4 of Lin et Jou (2000)" << endl;
    g = Graph("graph_fig4.txt", Graph::TYPE_ADJACENCY_LIST);
    g.print(true);
    cout << endl;
    cout << "Is {0,1,2} a clique ? ";
    vector<int> clique;
    clique.push_back(0);
    clique.push_back(1);
    clique.push_back(2);
    if (g.isClique(clique)) cout << "yes";
    else cout << "no";
    cout << endl;
    cout << "Is {0,1,5} a clique ? ";
    clique = vector<int>();
    clique.push_back(0);
    clique.push_back(1);
    clique.push_back(5);
    if (g.isClique(clique)) cout << "yes";
    else cout << "no";
    cout << endl;
    cout << "Adding a self-loop on 0" << endl;
    g.addEdge(0, 0);
    cout << "Is {0,1,5} a clique ? ";
    clique = vector<int>();
    clique.push_back(0);
    clique.push_back(1);
    clique.push_back(5);
    if (g.isClique(clique)) cout << "yes";
    else cout << "no";
    cout << endl;
    cout << "Removing the self-loop" << endl;
    g.deleteEdge(0, 0);
    cout << "Trying the CORE operator" << endl;
    cout << "Pi-vertices : ";
    piVertices = g.piVertices();
    for (vector<int>::iterator it = piVertices.begin(); it != piVertices.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl << "Vertices ";
    vector<int> coreVertices = g.core();
    for (vector<int>::iterator it = coreVertices.begin(); it != coreVertices.end(); ++it)
        cout << *it << " ";
    cout << "have been removed." << endl;
    g.print(true);
    cout << endl;

    cout << "Loading graph of Figure 6 of Lin et Jou (2000)" << endl;
    g = Graph("graph_fig6.txt", Graph::TYPE_ADJACENCY_LIST);
    g.print(true);
    cout << endl;
    cout << "Pi-predecessors of 5 : ";
    vector<int> piPreds = g.piPredecessors(5);
    for (vector<int>::iterator it = piPreds.begin(); it != piPreds.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "Non-pi-predecessors of 5 : ";
    vector<int> nonPiPreds = g.nonPiPredecessors(5);
    for (vector<int>::iterator it = nonPiPreds.begin(); it != nonPiPreds.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "Is (2,5) dominated (should be) ? ";
    if (g.isDominated(2, 5)) cout << "yes";
    else cout << "no";
    cout << endl;
    cout << "Dominated edges : ";
    vector<Edge> dominatedEdges = g.dominatedEdges();
    for (vector<Edge>::iterator it = dominatedEdges.begin(); it != dominatedEdges.end(); ++it)
        cout << "(" << it->source << "," << it->target << ") ";
    cout << endl;
    cout << "Applying DOME" << endl;
    g.dome();
    g.print(true);
    cout << endl << endl;

    cout << "Timing the application of the eight operators on CIDE (665 vertices)" << endl;
    g = Graph("cide_reduced.txt", Graph::TYPE_ADJACENCY_LIST);
    g.print(false);
    cout << endl;
    clock_t startTime = clock();
    cout << "Applying the eight operators once" << endl;
    g.reduce(true, true, true, true, true, true, true, true, true);
    cout << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    g.print(false);
    cout << endl;
    cout << "Reducing the graph";
    g.reduce(true);
    g.print(false);
    cout << endl << endl;

    cout << "Reloading graph of Figure 6 of Lin et Jou (2000)" << endl;
    g = Graph("graph_fig6.txt", Graph::TYPE_ADJACENCY_LIST);
    g.print(true);
    cout << endl;
    cout << "Is {0,1,2,3,4,5} a feedback vertex set ? ";
    vector<int> fvs;
    fvs.push_back(0); fvs.push_back(1); fvs.push_back(2);
    fvs.push_back(3); fvs.push_back(4); fvs.push_back(5);
    if (g.isFeedbackVertexSet(fvs)) cout << "yes";
    else cout << "no";
    cout << endl;
    fvs = vector<int>();
    fvs.push_back(0); fvs.push_back(2); fvs.push_back(4);
    cout << "Is {0,2,4} a feedback vertex set ? ";
    if (g.isFeedbackVertexSet(fvs)) cout << "yes";
    else cout << "no";
    cout << endl;
    fvs = vector<int>();
    fvs.push_back(0);
    cout << "Is {0} a feedback vertex set ? ";
    if (g.isFeedbackVertexSet(fvs)) cout << "yes";
    else cout << "no";
    cout << endl;
    fvs = vector<int>();
    fvs.push_back(1); fvs.push_back(3);
    fvs.push_back(4); fvs.push_back(5);
    cout << "Is {1,3,4,5} a feedback vertex set ? ";
    if (g.isFeedbackVertexSet(fvs)) cout << "yes";
    else cout << "no";
    cout << endl << endl;

    // Long test
    //cout << "Reloading CIDE reduced graph (665 vertices)" << endl;
    //g = Graph("cide_reduced.txt", Graph::TYPE_ADJACENCY_LIST);
    //g.print(false);
    //cout << endl;
    //cout << "Computing an upper bound" << endl;
    //startTime = clock();
    //fvs = g.upperBoundSolution(false);
    //cout << "Took ";
    //cout << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    //cout << "An upper bound solution : ";
    //for (vector<int>::iterator it = fvs.begin(); it != fvs.end(); ++it)
    //    cout << *it << " ";
    //cout << endl;
    //cout << "Size of the solution : " << fvs.size() << endl;
    //cout << "Is it really a solution ? ";
    //if (g.isFeedbackVertexSet(fvs)) cout << "yes";
    //else cout << "no";
    //cout << endl;

    cout << "Reloading graph of Figure 6 of Lin et Jou (2000)" << endl;
    g = Graph("graph_fig6.txt", Graph::TYPE_ADJACENCY_LIST);
    g.print(true);
    cout << endl;
    cout << "A shortest cycle : [ ";
    vector<int> cycle = g.shortestCycle();
    for (vector<int>::iterator it = cycle.begin(); it != cycle.end(); ++it)
        cout << *it << " ";
    cout << "]";
    cout << endl;
    cout << "The subgraph induced by {1,2,4}" << endl;
    vector<int> vs;
    vs.push_back(1);
    vs.push_back(2);
    vs.push_back(4);
    h = g.subgraph(vs);
    h.print(true);
    cout << endl;

    // Long test
    cout << endl << endl;
    cout << "Reloading CIDE reduced graph (665 vertices)" << endl;
    g = Graph("cide_reduced.txt", Graph::TYPE_ADJACENCY_LIST);
    g.print(false);
    cout << endl;
    cout << "Computing a lower bound" << endl;
    startTime = clock();
    int lb = g.lowerBoundValue(false);
    cout << "Took ";
    cout << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "The lower bound value : " << lb << endl;
    cout << endl;

    //cout << endl;
    //cout << "Loading a graph of 100 vertices" << endl;
    //g = Graph("graph100.txt", Graph::TYPE_ADJACENCY_LIST);
    //g.print(true);
    //cout << endl;
    //h = Graph(g);
    //cout << "Reduced graph : ";
    //h.reduce();
    //h.print(true);
    //cout << endl;
    //cout << "An upper bound : " << g.upperBoundValue() << endl;
    //cout << "A lower bound  : " << g.lowerBoundValue() << endl;
    //cout << "A minimum feedback vertex set : ";
    //vector<int> mfvs = g.minimumFeedbackVertexSet(true);
    //for (vector<int>::iterator it = mfvs.begin(); it != mfvs.end(); ++it)
    //    cout << *it << " ";
    //cout << endl;
    //cout << "Is it really a feedback vertex set ? ";
    //if (g.isFeedbackVertexSet(mfvs)) cout << "yes";
    //else cout << "no";
}

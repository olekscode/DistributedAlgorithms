package com.somename.name

import scala.reflect.ClassTag
import org.apache.spark.graphx.lib.TriangleCount
import org.apache.spark.graphx.Graph

object MyTriangleCount {
  def modifiedRun[VD: ClassTag, ED: ClassTag](graph: Graph[VD, ED]): Graph[Int, ED] = {
    println("\033[38;5;2mI have modified this function!\033[0m")

    // Transform the edge data something cheap to shuffle and then canonicalize
    val canonicalGraph = graph.mapEdges(e => true).removeSelfEdges().convertToCanonicalEdges()
    // Get the triangle counts
    val counters = TriangleCount.runPreCanonicalized(canonicalGraph).vertices
    // Join them bath with the original graph
    graph.outerJoinVertices(counters) { (vid, _, optCounter: Option[Int]) =>
      optCounter.getOrElse(0)
    }
  }
}
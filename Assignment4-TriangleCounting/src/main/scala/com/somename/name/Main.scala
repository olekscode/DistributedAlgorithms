package com.somename.name

import org.apache.spark.SparkConf
import org.apache.spark.SparkContext
import org.apache.spark.graphx.{GraphLoader, PartitionStrategy}

object Main {
  def main(args: Array[String]) = {
    val conf = new SparkConf()
      .setAppName("Triangle Counting")
      .setMaster("local[*]")

    val sc = new SparkContext(conf)

    val graph = GraphLoader.edgeListFile(sc, "/etc/followers.txt")
      .partitionBy(PartitionStrategy.RandomVertexCut)

    val triCounts = MyTriangleCount.modifiedRun(graph).vertices
    //triCounts.take(6)

    val result = (triCounts.values.sum() / 3.0).toInt

    // triCounts.map(_._2).sum()

    // val result = triCounts.map(_._2).reduce(_+_)

    println(s"\033[38;5;2mThis graph has $result triangles\033[0m")
  }
}


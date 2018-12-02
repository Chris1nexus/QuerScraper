package com.nexlabs.quervminer;

public class TestTree {
	
	public static final String ROOT_PATH = "fmgroup.polito.it/quer/teaching/";
//	public static void main(String args[]) {
//		
//		QNode node = new QDirectory("/so/", null);
//		QNode files = new QDirectory("files/", node) ;
//		
//		node.addChildQNode(files);
//		node.addChildQNode(new QDirectory("downloads/", node) );
//		node.addChildQNode(new QFile("myfile.txt", node) );
//		
//		QFile file = new QFile("last.txt", files);
//		
//		files.addChildQNode(new QFile("last.txt", files));
//		node.visit();
//		
//		System.out.println(file.resolvedPath());
//	}
//	
	
	public static void main(String args[]) {
		JTreeBuilder.execute();
	}


}

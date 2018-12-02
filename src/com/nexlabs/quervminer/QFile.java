package com.nexlabs.quervminer;

public class QFile extends QNode{

	
	public QFile(String path, QNode parent) {
		super(path, parent);
	}
	


	@Override
	public boolean isLeaf() {
		return true;
	}

	
	
}

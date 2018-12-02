package com.nexlabs.quervminer;

import java.util.List;

public class QDirectory extends QNode {

	

	public QDirectory(String path, QNode parent) {
		super(path, parent);
		
	}



	@Override
	public boolean isLeaf() {
		return false;
	}

}

package com.nexlabs.quervminer;

import java.util.ArrayList;
import java.util.List;

public abstract class QNode {
	
	
	String path;
	String parentPath;
	QNode parent;
	List<QNode> childs;
	
	
	public QNode(String path, QNode parent) {
		super();
		this.path = path;
		//this.parentPath = parentPath;
		this.parent = parent;
		//if(! isLeaf()) {
		this.childs = new ArrayList<>();
		//}
	}
	public boolean addChildQNode(QNode node) {
		if(this.isLeaf()) {
			return false;
		}
		childs.add(node);
		return true;
	}
//	public boolean setParentQNode(QNode parent) {
//		if(this.parent == null) {
//			this.parent = parent;
//			return true;
//		}
//		return false;
//	}
//	
	
	
	public abstract boolean isLeaf();
	public String getPath() {
		return path;
	}
	public String getParentPath() {
		return parentPath;
	}
	public QNode getParent() {
		return parent;
	}
	public List<QNode> getChilds() {
		return childs;
	}
	public void visit() {
		this.visitR(0);
		
	}
	private void visitR(int count) {
		System.out.println(QNode.addSpaces(count) + getPath() + "\n");
		for(QNode node : childs) {
			node.visitR(count + 1);
		}
		return;
		
	}
	
	public String resolvedPath() {
		QNode parent = this.parent;
		StringBuffer sbPath = new StringBuffer();
		sbPath.append(getPath());
		while(parent != null) {
			sbPath.insert(0, parent.getPath());
			parent = parent.getParent();
		}
		return new String(sbPath);
		
	}
	private static String addSpaces(int count) {
		char arr[] = new char[2*count + 1];
		int i = 0;
		for(i = 0; i < 2*count; i++) {
			arr[i] = ' ';
		}
		arr[i] = '\0';
		return new String(arr);
	}
	

}

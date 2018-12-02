package com.nexlabs.quervminer;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.FileSystems;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.jsoup.Connection.Response;
import org.jsoup.Jsoup;
import org.jsoup.helper.HttpConnection;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class JTreeBuilder {

	public static final String PARENT_DIR = "/quer/teaching/";
	
	public static final String DTOP_PATH = FileSystems.getDefault().getPath("").toAbsolutePath().toString();
	

	public static void execute() {
		String sitePath = TestTree.ROOT_PATH + "so/";
		isContentPage("/so/teaching.htm");

		String strUrl = "http://fmgroup.polito.it/quer/teaching/";

		QNode root = build(strUrl);
		
		root.visit();

}
	
	
	
	public static QNode build(String rootUrl) {
		try {
			String strUrl = "http://fmgroup.polito.it/quer/teaching/";

			QNode root = new QDirectory(strUrl, null);
			Response response = executeRequest(strUrl);
			
			
			return root;
		}catch(MalformedURLException e) {
			e.printStackTrace();
		}catch(IOException e) {
			e.printStackTrace();
		}
		
		return null;
	}
	public static void loadChilds(QNode parent, Response parentResponse) {
		try {
			String currentUrl = parentResponse.url().toString();
			
			String filePath = new URI(parent.resolvedPath()).getPath();
			File f = new File(DTOP_PATH +filePath);
			
			if(!f.exists()){
				//f.mkdir();
				System.out.println(f.getAbsolutePath());
				if(parent.isLeaf() == false) {
					System.out.println("XXXXX + " + filePath);
					f.mkdirs();
				}
			
				if(parent.isLeaf()) {
					System.out.println( "YYYYY");
					BufferedInputStream in = new BufferedInputStream(new ByteArrayInputStream( parentResponse.bodyAsBytes() ) );
					FileOutputStream out = new FileOutputStream( DTOP_PATH +filePath);
					System.out.println(parent.resolvedPath());
					byte arr[] = new byte[1024];
					int n = 0;
					
					while( (n = in.read(arr, 0, 1024)) != -1 ) {
						out.write(arr, 0, n);
					}
					
					in.close();
					out.close();
				}
					
					
				//}
				
			}
			
			
			Elements list = Jsoup.parse(parentResponse.body()).getElementsByTag("a");
				
			for(Element el : list) {
				
				String relPath = el.attr("href");
				
				String childUrl =  currentUrl + relPath;
				
				QNode node = null;
				if( (node = buildQNode(relPath, parent)) != null ) {
					System.out.println(el.attr("href") + ":\n");
					
					Response res = executeRequest(childUrl );
					parent.addChildQNode(node);
					loadChilds(node, res);
				}
			}
				
				
			
		}catch(IOException e) {
			e.printStackTrace();
		} catch (URISyntaxException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	public static String formatName(QNode node, Response response) {
		
		return null;
	}
	
	
	
	public static QNode buildQNode(String path, QNode parent) {
		if(isRedirect(path)) {
			return null;
		}
		if(isPath(path)) {
			QNode dir = new QDirectory(path, parent);
			File f = new File(dir.resolvedPath());
			if(!f.exists()) {
				f.mkdir();
			}
			
			return dir;
		}else if(isContentPage(path)  && (!path.contains("htm") ) ) {
			QNode file = new QFile(path, parent);
			System.out.println("file");
			//File f = new File(file.resolvedPath());

			return file;
		}
		
		return null;
		
	}
	
	
	public static Response executeRequest(String url) throws IOException {
		HttpConnection conn = (HttpConnection) Jsoup.connect(url);
		conn.ignoreContentType(true);
		
		Response response = conn.execute();
		return response;
	}
	
	public static boolean isPath(String path) {
		Pattern pathPattern = Pattern.compile("(?:/?([^/]+)/){1,}");
		Matcher m = pathPattern.matcher(path);
		if(m.matches()) {
			//System.out.println("matched : " + m.group(0));
			return true;
		}
		
		return false;
	}
	public static boolean isRedirect(String path) {
		return path.equals(PARENT_DIR) || path.contains("/quer/");
	}
	
	public static boolean isContentPage(String path) {
		try {
			URI uri = new URI(path);
			path = uri.getPath();
			Pattern pathPattern = Pattern.compile("(?:/?(?:[^/]+)/){0,}([-+A-Za-z0-9%]+(?:.[-+A-Za-z0-9%]+){1,})");
			Matcher m = pathPattern.matcher(path);
			if(m.matches()) {
				//System.out.println("matched : " + m.group(1));
				return true;
			}
			
		} catch (URISyntaxException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		return false;
	}
	
	
	
	
}

//
//  IndexViewController.m
//  Baker
//
//  ==========================================================================================
//  
//  Copyright (c) 2010-2011, Davide Casali, Marco Colombo, Alessandro Morandi
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without modification, are 
//  permitted provided that the following conditions are met:
//  
//  Redistributions of source code must retain the above copyright notice, this list of 
//  conditions and the following disclaimer.
//  Redistributions in binary form must reproduce the above copyright notice, this list of 
//  conditions and the following disclaimer in the documentation and/or other materials 
//  provided with the distribution.
//  Neither the name of the Baker Framework nor the names of its contributors may be used to 
//  endorse or promote products derived from this software without specific prior written 
//  permission.
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
//  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  

#import "IndexViewController.h"


@implementation IndexViewController

- (id)initWithBookBundlePath:(NSString *)path documentsBookPath:(NSString *)docpath fileName:(NSString *)name webViewDelegate:(UIViewController<UIWebViewDelegate> *)delegate {
    bookBundlePath = path;
    documentsBookPath = docpath;
    fileName = name;
    webViewDelegate = delegate;
    disabled = NO;
    indexHeight = 0;
    
    // ****** INIT PROPERTIES
    properties = [Properties properties];
    
    [self setPageSizeForOrientation:UIInterfaceOrientationPortrait];
    
    return [self initWithNibName:nil bundle:nil];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
    // Initialization to 1x1px is required to get sizeThatFits to work
    UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 1024, 1, 1)];
    webView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
    webView.delegate = self;
    
    webView.backgroundColor = [UIColor clearColor];
    [webView setOpaque:NO];
    
    self.view = webView;
    [webView release];
    
    [self loadContent];
}

- (void)setBounceForWebView:(UIWebView *)webView bounces:(BOOL)bounces {
    for (id subview in webView.subviews)
        if ([[subview class] isSubclassOfClass: [UIScrollView class]])
            ((UIScrollView *)subview).bounces = bounces;
}

- (void)setPageSizeForOrientation:(UIInterfaceOrientation)orientation {
	CGRect screenBounds = [[UIScreen mainScreen] bounds];
	
	if (orientation == UIInterfaceOrientationLandscapeLeft || orientation == UIInterfaceOrientationLandscapeRight) {
		pageWidth = screenBounds.size.height;
		pageHeight = screenBounds.size.width;
    } else {
        pageWidth = screenBounds.size.width;
		pageHeight = screenBounds.size.height;
	}
    
    UIApplication *sharedApplication = [UIApplication sharedApplication];
    if (sharedApplication.statusBarHidden) {
        pageY = 0;
    } else {
        pageY = -20;
    }
    
    NSLog(@"Set IndexView size to %dx%d, with pageY set to %d", pageWidth, pageHeight, pageY);
}

- (BOOL)isIndexViewHidden {
    return [UIApplication sharedApplication].statusBarHidden;
}

- (BOOL)isDisabled {
    return disabled;
}

- (void)setIndexViewHidden:(BOOL)hidden withAnimation:(BOOL)animation {
    CGRect frame;
    if (hidden) {
        frame = CGRectMake(0, pageHeight + pageY, pageWidth, indexHeight);
    } else {
        frame = CGRectMake(0, pageHeight + pageY - indexHeight, pageWidth, indexHeight);
    }
    
    if (animation) {
        [UIView beginAnimations:@"slideIndexView" context:nil]; {
            [UIView setAnimationDuration:0.3];
            
            self.view.frame = frame;
        }
        [UIView commitAnimations];
    } else {
        self.view.frame = frame;
    }
    
}

- (void)fadeOut {
    [UIView beginAnimations:@"fadeOutIndexView" context:nil]; {
        [UIView setAnimationDuration:0.0];
        
        self.view.alpha = 0.0;
    }
    [UIView commitAnimations];
}

- (void)fadeIn {
    [UIView beginAnimations:@"fadeInIndexView" context:nil]; {
        [UIView setAnimationDuration:0.2];
        
        self.view.alpha = 1.0;
    }
    [UIView commitAnimations];
}

- (void)willRotate {
    [self fadeOut];
}

- (void)rotateFromOrientation:(UIInterfaceOrientation)fromInterfaceOrientation toOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    BOOL hidden = [self isIndexViewHidden]; // cache hidden status before setting page size
    
    [self setPageSizeForOrientation:toInterfaceOrientation];
    [self setIndexViewHidden:hidden withAnimation:NO];
    [self fadeIn];
}
- (void)loadContent{
    [self loadContentFromBundle:true];
}

- (void)loadContentFromBundle:(BOOL)fromBundle{
    NSString* path;
    if(fromBundle){
        NSLog(@"Reloading index from bundle");
        path = [bookBundlePath stringByAppendingPathComponent:fileName];
    } else {
        path = [documentsBookPath stringByAppendingPathComponent:fileName];
    }
    
    [self assignProperties];
    
    NSLog(@"Path to index view is %@", path);
    if ([[NSFileManager defaultManager] fileExistsAtPath:path]) {
        disabled = NO;
		[(UIWebView *)self.view loadRequest:[NSURLRequest requestWithURL:[NSURL fileURLWithPath:path]]];
	} else {
        NSLog(@"Could not find index view at that path");
        disabled = YES;
    }
}

- (void)assignProperties {
    UIWebView *webView = (UIWebView*) self.view;
    webView.mediaPlaybackRequiresUserAction = ![[properties get:@"-baker-media-autoplay", nil] boolValue];
    
    BOOL bounce = [[properties get:@"-baker-index-bounce", nil] boolValue];
    [self setBounceForWebView:webView bounces:bounce];
}

-(void)webViewDidFinishLoad:(UIWebView *)webView {
    id height = [properties get:@"-baker-index-height", nil];
    if (height != [NSNull null]) {
        indexHeight = (int) [height integerValue];
    } else {
        indexHeight = [webView sizeThatFits:CGSizeZero].height;        
    }
    NSLog(@"Set height for IndexView to %d", indexHeight);
    
    // After the first load, point the delegate to the main view controller
    webView.delegate = webViewDelegate;
}

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
}
*/

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

@end

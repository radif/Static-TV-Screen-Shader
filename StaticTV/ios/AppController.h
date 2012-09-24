//
//  StaticTVAppController.h
//  StaticTV
//
//  Created by Radif Sharafullin on 9/23/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end


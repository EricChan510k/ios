//
//  TPSyncHandlerDelegate.h
//  teachpoint
//
//  Created by Noah Beamen on 7/24/12.
//  Copyright (c) 2012 Clear Pond Technologies, Inc. All rights reserved.
//

@protocol TPSyncHandlerDelegate
- (void)didFinishSyncHandler:(NSArray *)appList;
- (void)syncHandlerErrorOccurred:(NSString *)error;
@end

@class TPUser;
@class TPSyncHandlerOp;

#import "TPModel.h"
#import "TPSyncHandlerDelegate.h"

// ---------------------------------------------------------------------------------------
typedef enum {
    SYNC_TYPE_UNKNOWN = 0,
    SYNC_TYPE_USER = 1,
    SYNC_TYPE_INFO = 2,
    SYNC_TYPE_CATEGORY = 3,
    SYNC_TYPE_RUBRIC = 4,
    SYNC_TYPE_CLIENTDATA = 5,
    SYNC_TYPE_CLIENTIMAGE = 6,
    SYNC_TYPE_DATA = 7,
    SYNC_TYPE_IMAGEDATA = 8,
} TPModelSyncType;

typedef enum {
	SYNC_ERROR_OK = 0,
	SYNC_ERROR_GENERAL = -1,
	SYNC_ERROR_WIFI = -2,
	SYNC_ERROR_TIMEOUT = -3,
	SYNC_ERROR_LOGIN = -4
} TPModelSyncError;

// ---------------------------------------------------------------------------------------
@interface TPModel (Sync) <TPSyncHandlerDelegate>

- (void) syncinit;
- (void) updateLastSync;
- (void) immediateSync;
- (void) suspendSyncing;
- (void) restartSyncing;
- (BOOL) syncIsSupended;
- (NSDate *) getLastSync;
- (int) getUserDataUnsyncedCount;

- (void) registerSyncStatusCallback:(id) delegate :(SEL)selector;
- (void) unregisterSyncStatusCallback;
- (void) updateSyncStatus:(int) status;

- (NSString *) syncEncode:(NSString *)rawstring;
- (NSString *) syncDecode:(NSString *)rawstring;
- (NSString *) postRequestEncode:(NSString *)input;

- (void) doSync:(int)syncType;
- (void) cancelSync;
- (void) clientDataSyncPrep;
- (int) getUnsyncedCount;
- (int) getUnprocessedCount;

- (void) setDatabaseSavepointWithName:(NSString*) savepointName;
- (void) releaseDatabaseSavepointWithName:(NSString*) savepointName;
- (void) rollbackToDatabaseSavepointWithName:(NSString*) savepointName;

- (NSString *) getUserListXMLEncoding;
- (NSString *) getInfoListXMLEncoding;
- (NSString *) getCategoryListXMLEncoding;
- (NSString *) getRubricListXMLEncoding;

- (void) handleUserSyncData;
- (void) handleUserInfoSyncData;
- (void) handleCategorySyncData;
- (void) handleRubricSyncData;
- (void) handleImageSyncData;
- (void) handleUserDataSyncData:(TPSyncHandlerOp *)callingOperation;
- (BOOL) handleUserDataSyncDataSubset:(TPSyncHandlerOp *)callingOperation target_id:(int)target_id;
- (void) handleDeletedData;

- (void) markAllUsersAsUnsynced;

@end

// ---------------------------------------------------------------------------------------

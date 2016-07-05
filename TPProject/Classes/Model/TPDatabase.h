#import <sqlite3.h>
#import "TPModel.h"
#import "NSData+Base64.h"

@class TPModel;
@class TPQuestion;
@class TPRating;
@class TPImage;

// --------------------------------------------------------------------------------------
@interface TPDatabase : NSObject {

	TPModel *model;
	sqlite3 *database;
    NSString *imagesPath;
    
    NSDateFormatter *dateformatter;
    NSLocale *dateLocal;
    NSLock *dateformatterLock;
}

@property (nonatomic, retain) NSString *imagesPath;

- (id) initWithModel:(TPModel *)some_model;

// Basic operations
- (void) initDatabase;

- (void) closeDatabase;
+ (void) destroyDatabase;
+ (void) deleteAllImageFiles;
- (void) clear;

- (void) dumpDatabase;
- (void) dumpDatabaseShort;
+ (void) dumpImageDirContents;

- (void) deleteData:(NSString *)tablename;

// Operations on user data object
- (int) numUserData;
- (TPUserData *) getUserData:(NSString *)userdata_id;
- (void) getUserDataList:(NSMutableArray *)userdata target:(int)target_id filterUserId:(int)filterUserId;
- (void) getImageList:(NSMutableArray *)userdata_list target:(int)target_id filterUserId:(int)filterUserId;

- (NSDictionary *) getTotalElapsedByUserId:(int)filterUserId;
- (NSDictionary *) getTotalFormsByUserId:(int)filterUserId;

- (void) getImageListByUserdataId:(NSMutableArray *)image_list userdataId:(NSString *)userdataId;

- (BOOL) imageDataDoesExist:(NSString *)userdataId imageType:(int)imageType;
- (BOOL) imageFileDoesExist:(NSString *)userdataId imageType:(int)imageType;

- (int) getRubricIdFromUserdataID:(NSString *)userdata_id;
- (BOOL) purgeUserDataIfEmpty:(NSString *)userdata_id;
- (int) countUserDataEntries:(NSString *)userdata_id;

- (void) updateUserData:(TPUserData *)userdata setModified:(BOOL)setModified;
- (void) updateImage:(TPImage *)image;
- (void) updateImageOrigin:(NSString *)userdata_id type:(int)image_type origin:(int)neworigin;
- (void) updateUserDataShare:(NSString *)userdata_id share:(int)newshare;
- (void) updateUserData:(NSString *)userdata_id name:(NSString *)newname share:(int)newshare description:(NSString *)newdescription;
- (int) getUserDataState:(NSString *)userdata_id;
- (void) updateUserDataState:(NSString *)userdata_id state:(int)newstate;
- (void) updateUserDataStateNoTimestamp:(NSString *)userdata_id state:(int)newstate;
- (void) updateUserDataElapsed:(NSString *)userdata_id elapsed:(int)newelapsed;
- (void) updateUserDataGrade:(NSString *)userdata_id grade:(int)newgrade;
- (void) deleteUserData:(NSString *)userdata_id includingImages:(BOOL)includingImages;

// Operations on rubric data
- (BOOL) ratingIsSelected:(TPRating *)rating question:(TPQuestion *)question userdata_id:(NSString *)userdata_id;
- (float) ratingValue:(TPRating *)rating question:(TPQuestion *)question userdata_id:(NSString *)userdata_id;
- (NSString *) questionText:(TPQuestion *)question userdata_id:(NSString *)userdata_id;
- (NSString *) questionAnnot:(TPQuestion *)question userdata_id:(NSString *)userdata_id;
- (NSDate *) questionDatevalue:(TPQuestion *)question userdata_id:(NSString *)userdata_id;
- (void) deleteRubricData:(int)rubric_id;
- (void) deleteImage:(NSString *)userdata_id imageType:(int)imageType;

// Operations used for syncing data
- (int) getUserDataUnsyncedCount;
- (void) getUserDataUnsyncedDataList:(NSMutableArray *)userdata_queue localImagesList:(NSMutableArray *)local_images_queue includeCurrentUserdata:(BOOL)includeCurrentUserdata;
- (BOOL) tryRestoreImageData:(NSString *)userdataId;
- (NSString *) getUserDataXMLEncoding:(NSString *)userdata_id;
- (NSString *) getUserDataListXMLEncoding;
- (NSString *) getLocalImageXMLEncoding:(NSString *)userdata_id;

- (void) getRecRubricList:(NSMutableArray *)userDataIdArray targetId:(int)target_id;

// Savepoint operations
- (void) setSavepointWithName:(NSString*) savepointName;
- (void) releaseSavepointWithName:(NSString*) savepointName;
- (void) rollbackToSavepointWithName:(NSString*) savepointName;

// Utility operations
- (NSString *) getTimestamp;
- (NSDate *) dateFromCharStr:(char *)date_str;
- (NSString *) stringFromDate:(NSDate *)date;
+ (NSString *) imagePathWithUserdataID:(NSString *)userdata_id suffix:(NSString *)suffix imageType:(int)imageType;

@end

// --------------------------------------------------------------------------------------

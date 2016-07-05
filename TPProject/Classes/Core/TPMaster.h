@class TPView;

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
typedef enum {
    TP_USER_SORT_NAME = 0,
    TP_USER_SORT_SCHOOL = 1,
    TP_USER_SORT_GRADE = 2
} TPUserSort;

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
@interface TPMasterVC : UIViewController <UITableViewDelegate, UITableViewDataSource, UIAlertViewDelegate> {
    
    TPView *viewDelegate;
    
	UITableView *table;
    UIView *headerView;
    UISegmentedControl *sortControl;
    UIImage *padlockImage;
    NSIndexPath *current_cell;
    UITableView *customTable;
    int current_sort;
    
    UIButton *greenSyncButton;
    UIButton *yellowSyncButton;
    UIActivityIndicatorView *syncSpinner;
    
}

- (id)initWithView:(TPView *)mainview;
- (void)resetPrompt;
- (void) sortUsersUIEvent;
- (void) sortUsers;
- (void) reloadTableData;
- (void) highlightTargetUser;
- (void) setNeedSyncButtonStateForStatus:(TPNeedSyncStatus)status;

@end

// --------------------------------------------------------------------------------------

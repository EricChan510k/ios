@class TPView;
@class TPRubricHeader;
@class TPRubricQRatingTable;
@class TPRubricQCellSubHeading;
@class TPGradePO;
@class TPQuestion;

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
#define TP_QUESTION_CELL_WIDTH										704
#define TP_QUESTION_CELL_WIDTH_EFFECTIVE							684
#define TP_QUESTION_TYPE_TEXT_TEXTVIEW_HEIGHT						39
#define TP_QUESTION_TYPE_TEXT_TEXTVIEW_HEIGHT_EDITED				110
#define TP_QUESTION_BEFORE_QUESTION_MARGIN                          10
#define TP_QUESTION_BEFORE_QUESTION_MARGIN_DATE                     4
#define TP_QUESTION_AFTER_QUESTION_MARGIN                           10
#define TP_QUESTION_BEFORE_PROMPT_MARGIN                            2
#define TP_QUESTION_AFTER_PROMPT_MARGIN                             2
#define TP_QUESTION_BUTTON_TOP_MARGIN                               4
#define TP_QUESTION_CATEGORY_TOP_MARGIN                             4
#define TP_QUESTION_DATE_TEXTFIELD_WIDTH                            220
#define TP_QUESTION_DATE_TEXTFIELD_HEIGHT                            28

#define TP_QUESTION_TYPE_RATING_CELL_LABEL_TAG						10
#define TP_QUESTION_TYPE_MULTISELECT_CELL_CHECKBOX_UNSELECTED_TAG	20
#define TP_QUESTION_TYPE_MULTISELECT_CELL_CHECKBOX_SELECTED_TAG		21
#define TP_QUESTION_TYPE_MULTISELECT_CELL_LABEL						22
#define TP_QUESTION_TYPE_MULTISELECT_CUMULATIVE_CELL_BUTTON			30

// --------------------------------------------------------------------------------------
// TPRubricVC - table of rubric questions.
// --------------------------------------------------------------------------------------
@interface TPRubricVC : UITableViewController <UITableViewDelegate, UITableViewDataSource> {
    
    TPView *viewDelegate;
    UIBarButtonItem *rightbutton;
    UISegmentedControl *expandController;
    TPRubricHeader *headerView;
	TPRubricQCellSubHeading *subHeadingView;    
	NSMutableArray *questionCells;
    int outline;
    UITextView *openTextView;
}

@property (readwrite, retain) NSMutableArray *questionCells;
@property (nonatomic, retain) UITextView *openTextView;

- (id) initWithView:(TPView *)mainview;
- (void) reset;
- (BOOL) updateElapsedTime;
- (void) finalizeRubricCells:(BOOL)forceClose;
- (NSIndexPath*) indexPathForQuestion: (TPQuestion*)question;
- (void) updateCellsUI;
- (BOOL) getOutline;

@end

// --------------------------------------------------------------------------------------
// TPRubricHeader - view used as header in rubric table
// --------------------------------------------------------------------------------------
@interface TPRubricHeader : UIView {
    
    TPView *viewDelegate;

    UILabel *target;
    UILabel *school;
}

- (id)initWithView:(TPView *)mainview;
- (void) reset;

@end

// --------------------------------------------------------------------------------------
// TPRubricQRatingCell - a cell class for rating question table
// --------------------------------------------------------------------------------------
@interface TPRubricQRatingCell : UITableViewCell {
    NSMutableArray *columns;
	int selectedRating;
}

@property (readwrite) int selectedRating;

- (void) addColumn:(CGFloat)position;
- (void) resetColumns;

@end

// --------------------------------------------------------------------------------------
// TPRubricQRatingTable - return content of rating selection list (table)
// --------------------------------------------------------------------------------------
@interface TPRubricQRatingTable : UITableView <UITableViewDelegate, UITableViewDataSource> {
    
    TPView *viewDelegate;
	NSMutableArray *ratingCells;
    TPQuestion *question;
	int ratingsCount;
	float headerCellHeight;
	float contentCellHeight;
	BOOL showAnswers;
}

@property (readwrite) BOOL showAnswers;
@property (readwrite) int ratingsCount;

- (id) initWithView:(TPView *)mainview question:(TPQuestion *)question frame:(CGRect)targetFrame;
- (TPRubricQRatingCell *)customCellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void) setAnswers:(BOOL)doShow;
- (BOOL) shouldDisableCollapsing;

@end

// --------------------------------------------------------------------------------------
// TPRubricQMultiSelectTable - return content of uni-/multi- selection list (table)
// --------------------------------------------------------------------------------------
@interface TPRubricQMultiSelectTable : UITableView <UITableViewDelegate, UITableViewDataSource> {
    
    TPView *viewDelegate;
    TPQuestion *question;
	int ratingsCount;
	NSMutableArray *multiSelectTableCells, *cellHeights;
	BOOL showAnswers;
}

@property (readwrite) BOOL showAnswers;
@property (readonly) float tableHeight;

- (id) initWithView:(TPView *)mainview question:(TPQuestion *)question frame:(CGRect)targetFrame;
- (TPRubricQRatingCell *)customCellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void) setAnswers:(BOOL)doShow;
- (BOOL) cellIsSelected:(int)index;
- (void) cellContentHider:(UITableViewCell*)cell :(BOOL)doHide;
- (BOOL) shouldDisableCollapsing;

@end

// --------------------------------------------------------------------------------------
// TPRubricQMultiSelectCumulativeTable - return content of cumulative multiselection list (table)
// --------------------------------------------------------------------------------------
@interface TPRubricQMultiSelectCumulativeTable : UITableView <UITableViewDelegate, UITableViewDataSource> {
    
    TPView *viewDelegate;
    TPQuestion *question;
	int ratingsCount;
	NSMutableArray *multiSelectTableCells, *cellHeights, *cellValues;
	BOOL showAnswers;
}

@property (readwrite) BOOL showAnswers;
@property (readonly) float tableHeight;

- (id) initWithView:(TPView *)mainview question:(TPQuestion *)question frame:(CGRect)targetFrame;
- (TPRubricQRatingCell *)customCellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void) setAnswers:(BOOL)doShow;
- (BOOL) cellIsSelected:(int)index;
- (void) cellContentHider:(UITableViewCell*)cell :(NSIndexPath*)indexPath :(BOOL)doHide;
- (BOOL) shouldDisableCollapsing;

@end

// --------------------------------------------------------------------------------------
// TPRubricQCell - base class for table cell for rubric question
// --------------------------------------------------------------------------------------
@interface TPRubricQCell : UITableViewCell {
	TPView *viewDelegate;
    TPQuestion *question;
    UILabel *title;
    UILabel *category;
    UILabel *prompt;
	float cellHeight;
	UIImage *nextImage;
	UIButton *nextButton;
    BOOL canEdit;
}

@property (readonly) float cellHeight;
@property (assign) TPQuestion *question;
@property (readwrite) BOOL canEdit;

- (void) updateModified;
- (void) updateModifiedCell;
- (void) scrollToNextAction;
- (void) reloadCellAction;
- (void) setCompressState:(BOOL)compress :(BOOL)outline;
- (void) updateUI;
- (void)reloadCell;
+ (UIColor *) getTextColor:(BOOL)canEdit;

@end

// --------------------------------------------------------------------------------------
// TPRubricQCellAnnotated - base class for table cell for rubric question with annotation
// --------------------------------------------------------------------------------------
@interface TPRubricQCellAnnotated : TPRubricQCell <UITextViewDelegate> {
    UITextView *annotText;
    UIButton *annotButton;
    BOOL annotForceClose;
    BOOL annotEditable;
    BOOL showAnnotation;
}

@property (nonatomic, retain) UITextView *annotText;
@property (nonatomic, retain) UIButton *annotButton;
@property (readwrite) BOOL annotForceClose;
@property (readwrite) BOOL annotEditable;

- (id) init;
- (void)dismissAnnotKeyboard;

@end  

// --------------------------------------------------------------------------------------
// TPRubricQCellSubHeading - return content of table cell for sub-heading data
// --------------------------------------------------------------------------------------
@interface TPRubricQCellSubHeading : UIView {
	TPView *viewDelegate;
	UILabel *title, *readonlymsg, *name, *school, *subject, *grade, *evaluator, *date, *elapsed;
	UILabel *nameCaption, *schoolCaption, *subjectCaption, *gradeCaption, *evaluatorCaption, *dateCaption, *elapsedCaption, *shareCaption;
	UIButton *changeGrade, *elapsedButton;
	UISwitch *shareSwitch;
	NSTimer *secondTimer;
	int elapsedTime;
	
	TPGradePO *gradePO;
	UIPopoverController *gradePOC;
}

@property (readwrite) int elapsedTime;

- (id)initWithView:(TPView *)mainview;
- (void)startStopElapsedAction;
- (void)stopElapsedTime;
- (void)changeGradeActionCallback:(NSNumber*)selected;
- (void) shareReset;

@end

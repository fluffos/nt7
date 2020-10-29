
 
/* 一張地圖的大小規範 */
#define MAP_WIDTH 	100	//寬
#define MAP_LENGTH 	100	//長

/* 可視區範圍, 長與寬皆必須為奇數, 人才能剛好在地圖正中央 */
/* 新增遮避範圍設定, 現在的 25:9 比例剛好, 若無需要應避免更改, 否則對於遮避計算會有問題 */
#define CITY_VISION_WIDTH 	25	//可視地圖大小-寬
#define CITY_VISION_LENGTH 	9	//可視地圖大小-長
#define AREA_VISION_WIDTH 	31	//可視地圖大小-寬
#define AREA_VISION_LENGTH 	9	//可視地圖大小-長

#define	AGRICULTURE_REGION	(1<<0)		// 農業區
#define	INDUSTRY_REGION		(1<<1)		// 工業區
#define	COMMERCE_REGION		(1<<2)		// 商業區
#define AREA_REGION		(1<<3)		// 郊區

#define GOVERNMENT		(1<<0)		// 政府建築
#define	ENTERPRISE		(1<<1)		// 企業集團建築
#define INDIVIDUAL		(1<<2)		// 私人建築

/* 地圖座標資料庫設定之 KEY 的定義 */
#define FLAGS		1	// 資料旗標
#define TYPE		2	// 建物型態
#define ROOM		3	// 房間型態或路徑
#define SPECIAL_EXIT	4	// 特殊出口
#define VALUE		6	// 土地價格

/* FLAGS 中的位元檢查項目定義 */
#define NO_MOVE		(1 << 0)	// 此格無法通行旗標
#define NO_VIEW         (1 << 1)  	// 此格無法被看見

/* 建物型態 TYPE 對應之型態 */
//
#define MOUNTAIN	1	//山脈
#define FOREST		2	//森林
#define RIVER		3	//河川
#define SEA		4	//海洋
//
#define ROAD		21	//道路
#define BRIDGE		22	//橋樑
//
#define DOOR		41	//門
#define WALL		42	//牆壁
#define RAMPART		43	//城牆
#define TOWER		44	//箭塔/炮塔
//
#define FARM		61	//農田
#define PASTURE		62	//牧場
#define FISHFARM	63	//養殖場
//
#define LIGHT		101	//路燈
#define POOL		102	//水池
#define PAVILION	103	//涼亭
#define TREE		104	//大樹
#define GRASS		105	//草皮
#define STATUE		106	//雕像

#define MAP_FOREST	0	// 森林型態的地圖
#define MAP_OCEAN	1	// 海洋型態的地圖



// maze.h

// 迷宫房间原型文件
#define ROOM_FILE       "/inherit/room/maze"

// 迷宫出口通向的房间
#define ROOM_EXIT_FILE  "/d/city/wumiao"

// 迷宫宝箱的文件
#define BAOXIANG_OB     "/clone/misc/baoxiang"

// 迷宫守护进程的心跳间隔
#define HEART_TIME 30           /* 五分钟检查一次       */

// 迷宫的生命周期
#define MAZE_LIFT_CYCLE 1800    /* 半个小时             */

// 迷宫的宏定义
#define LENGTH  8               /* 迷宫横向的房间数量   */
#define HEIGHT  8               /* 迷宫纵向的房间数量   */
#define BOX_NUM 4               /* 迷宫宝箱的数量       */
#define XIANJING_NUM 3          /* 迷宫陷阱的数量       */
#define NORTH   1               /* 朝北方向             */
#define SOUTH   2               /* 朝南方向             */
#define WEST    3               /* 朝西方向             */
#define EAST    4               /* 朝东方向             */
#define IS_ROAD 1               /* 房间位于路线上       */
#define IS_ROOM 2               /* 房间不位于路线上     */
#define CAN_WALK    1           /* 指定方向有出路       */
#define IS_WALL 9               /* 指定方向是墙壁       */
#define NOT_DEFINED 0           /* 尚未初始化           */
#define TO_NORTH    0           /* 迷宫是由南向北       */
#define TO_SOUTH    1           /* 迷宫是由北向南       */
#define TO_WEST     2           /* 迷宫是由东向西       */
#define TO_EAST     3           /* 迷宫是由西向东       */
#define MAP_COMM    1           /* 迷宫地图是普通模式   */
#define MAP_DEEP    2           /* 迷宫地图是详细模式   */
#define MAP_NONE    3           /* 迷宫地图是关闭模式   */

// 迷宫的陷阱类型
#define BUSY        1           /* 让玩家BUSY           */
#define TRIP        2           /* 让玩家摔到别的房间   */
#define LOSTMAP     3           /* 让迷宫地图失效       */
#define CHANGEMAP   4           /* 让迷宫地图刷新       */
#define WOUND       5           /* 让玩家受伤           */

// 迷宫的宝箱类型
#define SPECIAL_MAP 1           /* 迷宫地图变为详细模式 */ 
#define SPECIAL_DAN 2           /* 仙丹等物品           */
#define JINKUAI     3           /* 金块等物品           */
#define GOLD        4           /* 黄金                 */
#define OBJ         5           /* 任务物品             */
#define SPECIAL_OBJ 6           /* 好的任务物品         */
#define NPC_SKILL   7           /* 降低杀手的武功       */
#define GEM         8           /* 宝石碎片       */

void collect_all_maze_information();            /* 将所有的迷宫房间清理     */
void init_line(mapping maze);                   /* 初始化迷宫地图           */
void init_road(object room, mapping maze);      /* 初始化迷宫路线           */
void init_wall(object room, mapping maze);      /* 给路线上的房间制造岔路   */
object *finish_room(object room, mapping maze); /* 将呆死的房间打通         */
void init_room_exits(mapping maze);             /* 将房间的出口刷新         */
void init_special_room(mapping maze);           /* 给迷宫初始化宝箱和陷阱   */

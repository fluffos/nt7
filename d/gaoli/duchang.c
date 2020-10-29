// /d/gaoli/duchang
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "高丽赌场");
        set("long", @LONG
这里是高丽城最大的一家赌坊。当夜幕降临后，这里就格外热闹。
布置豪华的大厅里，充满了温暖和欢乐，酒香中混合着上等脂粉的香气，
银钱敲击，发出一阵阵清脆悦耳的声音。
LONG        
       );
set("exits", ([
                "east":__DIR__"zhuque-2",    
        ]));
       setup();
        replace_program(ROOM);
}

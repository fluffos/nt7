#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"千寻宝塔"NOR);
        set("long",@LONG
崇圣寺三塔主塔千寻居中，是三塔中最高的一座，共有十六层，
高三百余尺，与西安大小雁塔同是唐代密檐式建筑。塔下仰望，只见
塔矗云端，云移塔驻似有倾倒之势。塔的基座呈方形，分二层，下层
四周有石栏，栏的四角柱头雕有石狮；上层东面正中有石照壁，上有
黔国公沐英后裔洒世阶题的“永镇山川”四个大字，庄重雄奇，颇有
气魄。每层正面中央开卷龛，各置白色大理石佛像一尊。
LONG);
        set("outdoors", "天龙寺");
        set("exits", ([
                "south" : __DIR__"yz6",
                "north" : __DIR__"yz3",		
        ]));
	
        set("coor/x",-350);
  set("coor/y",-300);
   set("coor/z",20);
   setup();
}

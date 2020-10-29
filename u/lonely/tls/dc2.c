#include <ansi.h>
inherit ROOM;
string long_desc();
void create()
{
        set("short", GRN"点苍十九峰"NOR);
        set("long", (: long_desc :));
        set("resource/water", 1);
        set("outdoors", "大理");
        set("exits", ([
              "northup"  : __DIR__"dc1",
              "eastdown" : __DIR__"dc3",            
        ]));
        set("coor/x",-350);
  set("coor/y",-420);
   set("coor/z",10);
   setup();
}
string long_desc()
{
        string desc;

        switch( random(6) ) {
        case 0: desc =
"点苍山西三阳、兰峰两峰，峰势雄壮，险要之出不可胜数，且松林遍
布。人要上去，当真比登天还难。峰中一溪名曰“白石”，溪水色如白玉，
飞流直下。\n";        
                break;
        case 1: desc =
"点苍山西兰峰、雪人两峰，一绿林满覆，一冰雪笼罩，形神各异。峰
中冰雪溶水和天然山泉相汇，组成一到白帘瀑布，飞落直下，溅起阵阵水雾，
这便是有名的“双鸳”溪。\n";               
                break;
        case 2: desc =
"点苍山西雪人、应乐峰皆为高山雪峰。只见两峰耸立，直冲云霄，峰
上白雪层层覆盖，在阳光照耀下显得更加亮丽。冰雪溶水缓缓流下，一条条
小渠慢慢相汇，成一溪流名曰“隐仙”。\n";        
                break;
        case 3: desc =
"点苍山西应乐、观音两峰高矮相对，加上山间云雾缭绕，使之越发显
得神秘，相传观世音菩萨曾亲临此地游玩而不思归去。峰间流淌的“梅溪”
得名于溪旁那一片天然梅林。\n";        
                break;
        case 4: desc =
"点苍山西观音、中和两峰峰势平和，峰中奇花异草繁多。而峰下桃树
林更是一绝，远远望去，有如一片红云。“桃溪”从中淌过，带着红色的桃
花缓缓流下山去。\n";        
                break;
        case 5: desc =
"点苍山西中和、龙泉两峰气侯温和，乃是种植花草的理想之处。远远
可看见由大理花匠所开的一片片花圃，点点花红撒落在两峰之上。峰中“中
溪”流经之处更是花开似锦，美不胜收。\n";        
                break;
        }
        return desc;
}
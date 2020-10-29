// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m五[35m彩[36m祥[1;37m云[2;37;0m[2;37;0m", ({"wcxy"}));        
        set("gender", "男性");                
        set("long", "一只麒麟变的$YEL$五$MAG$彩$CYN$祥$HIW$云.[2;37;0m
它是紫色少女的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cwzlxr");
        set("owner_name", "紫色少女");
        set_temp("owner", "cwzlxr");
        set_temp("owner_name", "紫色少女");
        ::setup();
}

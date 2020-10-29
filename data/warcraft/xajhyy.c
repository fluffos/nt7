// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m白虎[2;37;0m[2;37;0m", ({"laohu"}));        
        set("gender", "男性");                
        set("long", "上古神兽[2;37;0m
它是伏西牛逼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xajhyy");
        set("owner_name", "伏西牛逼");
        set_temp("owner", "xajhyy");
        set_temp("owner_name", "伏西牛逼");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m琉璃虎[2;37;0m[2;37;0m", ({"gtiger"}));        
        set("gender", "男性");                
        set("long", "这是一只白虎，身上有浅灰色的花纹，是一种珍稀幻兽。[2;37;0m
它是黄迦蓝的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "green");
        set("owner_name", "黄迦蓝");
        set_temp("owner", "green");
        set_temp("owner_name", "黄迦蓝");
        ::setup();
}

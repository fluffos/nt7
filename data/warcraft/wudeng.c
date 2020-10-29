// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m闪了你的眼[2;37;0m[2;37;0m", ({"wdds"}));        
        set("gender", "男性");                
        set("long", "又快又闪。[2;37;0m
它是五灯大师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wudeng");
        set("owner_name", "五灯大师");
        set_temp("owner", "wudeng");
        set_temp("owner_name", "五灯大师");
        ::setup();
}

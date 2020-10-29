// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m阿拉丁[2;37;0m[2;37;0m", ({"sdds"}));        
        set("gender", "男性");                
        set("long", "阿拉丁神灯。[2;37;0m
它是三灯大师的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sandeng");
        set("owner_name", "三灯大师");
        set_temp("owner", "sandeng");
        set_temp("owner_name", "三灯大师");
        ::setup();
}

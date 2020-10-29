// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m龙王火[2;37;0m[2;37;0m", ({"qdds"}));        
        set("gender", "男性");                
        set("long", "龙王火，火龙王，龙王火起最难防。[2;37;0m
它是七灯大师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qideng");
        set("owner_name", "七灯大师");
        set_temp("owner", "qideng");
        set_temp("owner_name", "七灯大师");
        ::setup();
}

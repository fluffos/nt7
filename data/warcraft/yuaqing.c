// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m玉字一号丸[2;37;0m[2;37;0m", ({"yqa"}));        
        set("gender", "女性");                
        set("long", "建立看见了我惊愕[2;37;0m
它是西门玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yuaqing");
        set("owner_name", "西门玉");
        set_temp("owner", "yuaqing");
        set_temp("owner_name", "西门玉");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m湛蓝神兽[2;37;0m[2;37;0m", ({"shan_dragon"}));        
        set("gender", "男性");                
        set("long", "一只浑身散发淡淡微光的神兽，据说是天地第一道光所化。[2;37;0m
它是青衫隐隐的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shan");
        set("owner_name", "青衫隐隐");
        set_temp("owner", "shan");
        set_temp("owner_name", "青衫隐隐");
        ::setup();
}

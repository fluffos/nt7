// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "乖乖小白[2;37;0m
它是墨子鱼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoqs");
        set("owner_name", "墨子鱼");
        set_temp("owner", "xiaoqs");
        set_temp("owner_name", "墨子鱼");
        ::setup();
}

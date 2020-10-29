// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "我的乖乖小白[2;37;0m
它是墨子云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoqsa");
        set("owner_name", "墨子云");
        set_temp("owner", "xiaoqsa");
        set_temp("owner_name", "墨子云");
        ::setup();
}

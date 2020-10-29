// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("绘色千佳[2;37;0m[2;37;0m", ({"cici"}));        
        set("gender", "女性");                
        set("long", "绘色千佳是Erotica公司旗下AV女优[2;37;0m
它是哔哔啦啦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "marry");
        set("owner_name", "哔哔啦啦");
        set_temp("owner", "marry");
        set_temp("owner_name", "哔哔啦啦");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("卡啦[2;37;0m[2;37;0m", ({"kala"}));        
        set("gender", "女性");                
        set("long", "没啥个性就不描述了吧[2;37;0m
它是阿懒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wangzj");
        set("owner_name", "阿懒");
        set_temp("owner", "wangzj");
        set_temp("owner_name", "阿懒");
        ::setup();
}

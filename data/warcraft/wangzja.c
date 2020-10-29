// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞啊飞[2;37;0m[2;37;0m", ({"kalayo"}));        
        set("gender", "男性");                
        set("long", "飞啊飞[2;37;0m
它是懒哥米哦的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wangzja");
        set("owner_name", "懒哥米哦");
        set_temp("owner", "wangzja");
        set_temp("owner_name", "懒哥米哦");
        ::setup();
}

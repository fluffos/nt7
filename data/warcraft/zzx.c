// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿黄[2;37;0m[2;37;0m", ({"zzxxxx"}));        
        set("gender", "男性");                
        set("long", "一只小小鸟啊[2;37;0m
它是烦啦烦啦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zzx");
        set("owner_name", "烦啦烦啦");
        set_temp("owner", "zzx");
        set_temp("owner_name", "烦啦烦啦");
        ::setup();
}

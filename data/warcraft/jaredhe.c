// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小四[2;37;0m[2;37;0m", ({"xiaosi"}));        
        set("gender", "男性");                
        set("long", "看起来雄壮异常[2;37;0m
它是火锅年糕的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jaredhe");
        set("owner_name", "火锅年糕");
        set_temp("owner", "jaredhe");
        set_temp("owner_name", "火锅年糕");
        ::setup();
}

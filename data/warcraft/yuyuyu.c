// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玉兔[2;37;0m[2;37;0m", ({"yutu"}));        
        set("gender", "男性");                
        set("long", "好可爱的小兔子噢[2;37;0m
它是玉兔玉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yuyuyu");
        set("owner_name", "玉兔玉");
        set_temp("owner", "yuyuyu");
        set_temp("owner_name", "玉兔玉");
        ::setup();
}

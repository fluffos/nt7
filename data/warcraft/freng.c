// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m苍[1;31m炎[2;37;0m[2;37;0m", ({"rat"}));        
        set("gender", "男性");                
        set("long", "神兽[2;37;0m
它是风之痕的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "freng");
        set("owner_name", "风之痕");
        set_temp("owner", "freng");
        set_temp("owner_name", "风之痕");
        ::setup();
}

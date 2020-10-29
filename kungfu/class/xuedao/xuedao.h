// check recruit

int permit_recruit(object ob)
{
        if( query("detach/密宗", ob) || query("betrayer/密宗", ob) )
        {
                command("say 你离开了密宗们，就别回来！");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 判师之徒，哼！哼！我把你千刀万剐！");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "密宗" )
        {
                command("say 你不是已经有了师傅么，还来干什么？偷学我派秘技啊！");
                return 0;
        }

        return 1;
}

int permit_recruit(object ob)
{
        if( query("detach/丐帮", ob) || query("betrayer/丐帮", ob) )
        {
                command("say 嘿嘿，你当初走的时候是怎么说的？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我们丐帮行事堂堂正正，绝不接纳判师之徒。");
                return 0;
        }

        if( query("family/family_name", ob )
            && query("family/family_name", ob) != "丐帮" )
        {
                command("say 你既然已经有了名师指点，还来我们丐帮干什么？");
                return 0;
        }
        return 1;
}

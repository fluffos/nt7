int permit_recruit(object ob)
{
        if( query("detach/段氏皇族", ob) || query("betrayer/段氏皇族", ob) )
        {
                command("say 既然离开了我们段家，就不要回来了");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 哼，我们大理段氏最痛恨的就是不忠不义之徒。");
                return 0;
        }

/*
        if( query("born_family", ob) != "段氏皇族" )
        {
                command("shake");
                command("say 我们段家乃皇族出身，不收外人。");
                return 0;
        }
*/

        if( query("family/family_name", ob )
            && query("family/family_name", ob) != "段氏皇族" )
        {
                command("hmm");
                command("say 你当年跑出去的时候怎么就没想过要回来？");
                return 0;
        }

        return 1;
}

int permit_recruit(object ob)
{
        if( query("detach/唐门世家", ob) || query("betrayer/唐门世家", ob) )
        {
                command("say 你反复无常，我不能收你为徒！");
                return 0;
        }
        
        if( query("betrayer/times", ob) )
        {
                command("say 哼，我们唐门世家最痛恨的就是不忠不义之徒。"); 
                return 0;
        }
        
/*
        if( query("born_family", ob) != "唐门世家" && !query("reborn/times", ob) ) 
        {
                command("hmm");
                command("say 我们唐门世家乃世家出身，不收外人。"); 
                return 0;
        }
*/

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "唐门世家" )
        {
                command("hmm");
                command("say 你既然已经离家拜师，就应有所作为，又跑回来作甚？");
                return 0;
        }

        return 1;
}

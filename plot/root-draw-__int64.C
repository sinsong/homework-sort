void root_draw___int64()
{
    TCanvas *c = new TCanvas("c", "sort_benchmark___int64", 1200, 768);
    TMultiGraph *mg = new TMultiGraph();

    TGraph *g1 = new TGraph("data-__int64-heapsort.txt");
    g1->SetTitle("heap sort");
    g1->SetLineColor(kGreen);
    //g1->SetMarkerStyle(21);
    mg->Add(g1);

    TGraph *g2 = new TGraph("data-__int64-shellsort.txt");
    g2->SetTitle("shell sort");
    g2->SetLineColor(kRed);
    //g2->SetMarkerStyle(5);
    mg->Add(g2);

    TGraph *g3 = new TGraph("data-__int64-parallel_quicksort.txt");
    g3->SetTitle("parallel quicksort");
    g3->SetLineColor(kBlue);
    //g3->SetMarkerStyle(2);
    mg->Add(g3);

    mg->SetTitle("Sort Benchmark T=__int64; X number (N); Y time (ms)");
    mg->Draw("AL");
    //mg->GetXaxis()->SetTitle("X number(N)");
    //mg->GetYaxis()->SetTitle("Y time(ms)");

    TLegend *leg = new TLegend(0.15, 0.65, 0.45, 0.85);
    leg->SetHeader("algorithm", "C");
    leg->AddEntry(g1, "heap sort");
    leg->AddEntry(g2, "shell sort");
    leg->AddEntry(g3, "parallel quicksort");
    leg->Draw();

    c->Print("root_canvas___int64.png");
    c->Print("root_canvas___int64.svg");
    //c->BuildLegend();
    //gPad->Update();
    //gPad->Modified();
}
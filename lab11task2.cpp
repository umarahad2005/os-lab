/*
 * OS Lab 11 - Part C & D
 * Part C: Segmentation Simulation
 * Part D: Hybrid Paging + Segmentation Model
 */

 #include <iostream>
 #include <vector>
 #include <cmath>
 using namespace std;
 
 // ─────────────────────────────────────────────
 //  PART C: Segmentation Simulation
 // ─────────────────────────────────────────────
 struct Segment {
     int base;
     int limit;
 };
 
 void partC() {
     cout << "\n========== PART C: Segmentation Simulation ==========\n";
 
     int numSegments;
     cout << "Enter number of segments: ";
     cin >> numSegments;
 
     vector<Segment> segTable(numSegments);
 
     cout << "\nEnter segment table (base and limit for each segment):\n";
     for (int i = 0; i < numSegments; i++) {
         cout << "  Segment " << i << " -> Base: ";
         cin >> segTable[i].base;
         cout << "             Limit: ";
         cin >> segTable[i].limit;
     }
 
     char again = 'y';
     while (again == 'y' || again == 'Y') {
         int segNum, offset;
         cout << "\nEnter logical address:\n";
         cout << "  Segment number: ";
         cin >> segNum;
         cout << "  Offset        : ";
         cin >> offset;
 
         if (segNum < 0 || segNum >= numSegments) {
             cout << "  ERROR: Invalid segment number " << segNum << ".\n";
         } else if (offset >= segTable[segNum].limit) {
             cout << "  SEGMENTATION FAULT: Offset " << offset
                  << " exceeds limit " << segTable[segNum].limit
                  << " for Segment " << segNum << ".\n";
         } else {
             int physAddr = segTable[segNum].base + offset;
             cout << "  Valid Access -> Physical Address = "
                  << segTable[segNum].base << " + " << offset
                  << " = " << physAddr << "\n";
         }
 
         cout << "\nTranslate another address? (y/n): ";
         cin >> again;
     }
 }
 
 // ─────────────────────────────────────────────
 //  PART D: Hybrid – Segmentation + Paging
 // ─────────────────────────────────────────────
 struct HybridSegment {
     int numPages;
     int pageSize;
     vector<int> pageTable; // pageTable[page#] = frame number
 };
 
 void partD() {
     cout << "\n========== PART D: Hybrid Paging + Segmentation ==========\n";
 
     int numSegments;
     cout << "Enter number of segments: ";
     cin >> numSegments;
 
     vector<HybridSegment> segments(numSegments);
 
     for (int i = 0; i < numSegments; i++) {
         cout << "\n-- Segment " << i << " --\n";
         cout << "  Number of pages : ";
         cin >> segments[i].numPages;
         cout << "  Page size (bytes): ";
         cin >> segments[i].pageSize;
 
         segments[i].pageTable.resize(segments[i].numPages);
         cout << "  Enter frame numbers for each page:\n";
         for (int p = 0; p < segments[i].numPages; p++) {
             cout << "    Page " << p << " -> Frame: ";
             cin >> segments[i].pageTable[p];
         }
     }
 
     char again = 'y';
     while (again == 'y' || again == 'Y') {
         int segNum, pageNum, offset;
         cout << "\nEnter logical address:\n";
         cout << "  Segment number : ";
         cin >> segNum;
         cout << "  Page number    : ";
         cin >> pageNum;
         cout << "  Offset         : ";
         cin >> offset;
 
         // Validate segment
         if (segNum < 0 || segNum >= numSegments) {
             cout << "  ERROR: Invalid segment number " << segNum << ".\n";
         }
         // Validate page
         else if (pageNum < 0 || pageNum >= segments[segNum].numPages) {
             cout << "  ERROR: Invalid page number " << pageNum
                  << " for Segment " << segNum << " (has "
                  << segments[segNum].numPages << " pages).\n";
         }
         // Validate offset
         else if (offset < 0 || offset >= segments[segNum].pageSize) {
             cout << "  ERROR: Offset " << offset
                  << " exceeds page size " << segments[segNum].pageSize
                  << " for Segment " << segNum << ".\n";
         }
         else {
             int frame     = segments[segNum].pageTable[pageNum];
             int pageSize  = segments[segNum].pageSize;
             int physAddr  = frame * pageSize + offset;
 
             cout << "  Segment " << segNum
                  << ", Page " << pageNum
                  << ", Offset " << offset << "\n";
             cout << "  Frame number     = " << frame << "\n";
             cout << "  Physical Address = " << frame << " * " << pageSize
                  << " + " << offset << " = " << physAddr << "\n";
         }
 
         cout << "\nTranslate another address? (y/n): ";
         cin >> again;
     }
 }
 
 // ─────────────────────────────────────────────
 //  MAIN
 // ─────────────────────────────────────────────
 int main() {
     int choice;
     cout << "======================================\n";
     cout << "  OS Lab 11 - Memory Management\n";
     cout << "======================================\n";
     cout << "Select task:\n";
     cout << "  1. Part C: Segmentation Simulation\n";
     cout << "  2. Part D: Hybrid Paging + Segmentation\n";
     cout << "  3. Both (C then D)\n";
     cout << "Enter choice (1/2/3): ";
     cin >> choice;
 
     if (choice == 1)      partC();
     else if (choice == 2) partD();
     else if (choice == 3) { partC(); partD(); }
     else cout << "Invalid choice.\n";
 
     cout << "\nDone.\n";
     return 0;
 }
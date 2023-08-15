//
//  main.cpp
//  Checkers
//
//

#include <iostream>
#include <string>


const int g_size { 8 } ;
int blackCount { 12 } ;
int redCount { 12 } ;

const std::string g_P1 { "B" } ;
const std::string g_P2 { "R" } ;
const std::string g_P1King { "BK" } ;
const std::string g_P2King { "RK" } ;


void initialSetup ( std::string board [] [ g_size ] , const int& size ) ;

void printBoard ( std::string board [] [ g_size ] , const int& size ) ;

std::string inputMove ( std::string player ) ;

bool checkLegal ( std::string board [] [ g_size ] , int startCol , int startRow , int endCol , int endRow , std::string player , std::string playerKing ) ;

void updateBoard ( std::string board [] [ g_size ] , int startCol , int startRow , int endCol , int endRow , std::string player ) ;

void pieceToKing ( std::string board [] [ g_size ] , const int& size ) ;

int main()
{
    std::string checkersBoard [ g_size ] [ g_size ] ;
    
    initialSetup ( checkersBoard , g_size ) ;
    
    printBoard ( checkersBoard , g_size ) ;
    
    while ( true )
    {
        std::string move ;
        int startRow ;
        int startCol ;
        int endRow ;
        int endCol ;
        
        bool illegal { true } ;
        while ( illegal )
        {
            move = inputMove ( g_P1 ) ;
            
            startRow = 8 - ( move [ 1 ] - '0' ) ;
            startCol = move [ 0 ] - 'a' ;
            
            endRow = 8 - ( move [ 3 ] - '0' ) ;
            endCol = move [ 2 ] - 'a' ;
            
            illegal = checkLegal( checkersBoard , startCol , startRow , endCol , endRow , g_P1 , g_P1King) ;
            
            if ( illegal )
            {
                std::cout << "Invalid move!\n" ;
            }
        }

        updateBoard( checkersBoard , startCol , startRow , endCol , endRow , g_P1 ) ;
        
        pieceToKing( checkersBoard , g_size ) ;
        
        std::cout << "\n\n\n\n\n\n\n\n\n\n" ;

        printBoard ( checkersBoard , g_size ) ;
        
        if ( redCount == 0 )
        {
            std::cout << "\nBlack Wins!\n" ;
            break ;
        }
        
        illegal = true ;
        while ( illegal )
        {
            move = inputMove ( g_P2 ) ;
            
            startRow = 8 - ( move [ 1 ] - '0' ) ;
            startCol = move [ 0 ] - 'a' ;
            
            endRow = 8 - ( move [ 3 ] - '0' ) ;
            endCol = move [ 2 ] - 'a' ;
            
            illegal = checkLegal( checkersBoard , startCol , startRow , endCol , endRow , g_P2 , g_P2King ) ;
            
            if ( illegal )
            {
                std::cout << "Invalid move!\n" ;
            }
        }
        
        updateBoard( checkersBoard , startCol , startRow , endCol , endRow , g_P2 ) ;
        
        pieceToKing( checkersBoard , g_size ) ;
        
        std::cout << "\n\n\n\n\n\n\n\n\n\n" ;
        
        printBoard ( checkersBoard , g_size ) ;
        
        if ( blackCount == 0 )
        {
            std::cout << "\nRed Wins!\n" ;
            break ;
        }
    }
    
    return 0;
}

void initialSetup ( std::string board [] [ g_size ] , const int& size )
{
    for ( int row = 0 ; row < size ; ++row )
    {
        for ( int col = 0 ; col < size ; ++col )
        {
            if ( row < 3 )
            {
                if ( row % 2 == 0 && col % 2 != 0 )
                {
                    board [ row ] [ col ] = g_P2 ;
                }
                else if ( row % 2 != 0 && col % 2 == 0 )
                {
                    board [ row ] [ col ] = g_P2 ;
                }
                else
                {
                    board [ row ] [ col ] = ' ' ;
                }
            }
            else if ( row > 4 )
            {
                if ( row % 2 == 0 && col % 2 != 0 )
                {
                    board [ row ] [ col ] = g_P1 ;
                }
                else if ( row % 2 != 0 && col % 2 == 0 )
                {
                    board [ row ] [ col ] = g_P1 ;
                }
                else
                {
                    board [ row ] [ col ] = " " ;
                }
            }
            else
            {
                board [ row ] [ col ] = ' ' ;
            }
        }
    }
}

void printBoard ( std::string board [] [ g_size ] , const int& size )
{
    
    for ( int row = 0 ; row < size ; ++row )
    {
        
        // so we want to print out our rowNums
        std::cout << size - row << "  |  " ;
        
        
        for ( int col = 0 ; col < size ; ++col )
        {
            std::cout << board [ row ] [ col ] << "  |  ";
        }
        
        std::cout << '\n' ;
        
        for ( int i = 0 ; i < size * 6 + 4 ; ++i )
        {
            std::cout << '-' ;
        }
        
        std::cout << '\n' ;
    }
    
    std::cout << "   |  " ;
    for ( int i = 0 ; i < size ; ++i )
    {
        std::cout << static_cast<char>( i + 'a' ) << "  |  " ;
    }
}

std::string inputMove ( std::string player )
{
    std::cout << '\n' << player << " move: " ;
    
    std::string move ;
    std::getline ( std::cin >> std::ws , move ) ;
    
    return move ;
}

bool checkLegal ( std::string board [] [ g_size ] , int startCol , int startRow , int endCol , int endRow , std::string player , std::string playerKing )
{
    if ( startRow < 0 || startRow >= g_size || startCol < 0 || startCol >= g_size || endRow < 0 || endRow >= g_size || endCol < 0 || endCol >= g_size )
    {
        return true ;
    }
    
    if ( ( ( board [ startRow ] [ startCol ] != player && board [ startRow ] [ startCol ] != playerKing ) ) || board [ endRow ] [ endCol ] != " " )
    {
        return true ;
    }
    
    
    int rowDiff { abs( startRow - endRow ) } ;
    int colDiff { abs( startCol - endCol ) } ;
    
    
    if ( ( board [ startRow ] [ startCol ] == g_P1 && endRow - startRow > 0 ) || ( board [ startRow ] [ startCol ] == g_P2 && endRow - startRow < 0 ) )
    {
        return true ;
    }
    
    
    if ( rowDiff == 1 && colDiff == 1 )
    {
        return false ;
    }
    else if ( rowDiff == 2 && colDiff == 2 )
    {
        int midRow { ( startRow + endRow ) / 2 } ;
        int midCol { ( startCol + endCol ) / 2 } ;
        
        if ( board [ midRow ] [ midCol ] != player && board [ midRow ] [ midCol ] != " " && board [ midRow ] [ midCol ] != playerKing )
        {
            return false ;
        }
    }
    
    
    return true ;
}

void updateBoard ( std::string board [] [ g_size ] , int startCol , int startRow , int endCol , int endRow , std::string player )
{
    board [ endRow ] [ endCol ] = board [ startRow ] [ startCol ] ;
    board [ startRow ] [ startCol ] = ' ' ;
    
    if ( abs( startRow - endRow ) > 1 )
    {
        int midRow { ( startRow + endRow ) / 2 } ;
        int midCol { ( startCol + endCol ) / 2 } ;
        
        board [ midRow ] [ midCol ] = " " ;
        
        if ( player == g_P1 )
        {
            --redCount ;
        }
        else
        {
            --blackCount ;
        }
    }
}

void pieceToKing ( std::string board [] [ g_size ] , const int& size )
{
    for ( int row = 0 ; row < size ; row = row + size - 1 )
    {
        for ( int col = 0 ; col < size ; ++col )
        {
            if ( row == 0 && board [ row ] [ col ] == g_P1 )
            {
                board [ row ] [ col ] = g_P1King ;
            }
            else if ( row == size - 1 && board [ row ] [ col ] == g_P2 )
            {
                board [ row ] [ col ] = g_P2King ;
            }
        }
    }
}

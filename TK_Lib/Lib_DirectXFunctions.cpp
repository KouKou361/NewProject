#include	"Lib_DirectXFunctions.h"
#include	"Lib_misc.h"

#include	<memory>

HRESULT	LoadCSOFromFile( const char* _pFileName,
						 unsigned char** _ppOutBuffer,
						 long* _pOutBufferSize )
{
	//	ファイルを読み込む
	FILE*	fp = nullptr;
	fopen_s( &fp, _pFileName, "rb" );
	_ASSERT_EXPR_A( fp, "CSO File not found" );
	if( !fp )
		return	E_FAIL;	//	ファイルが存在しないので失敗定数を返す

	//	ファイルサイズを取得
	fseek( fp, 0, SEEK_END );
	long	CSOFileSize	= ftell( fp );

	//	ファイルを読み込む
	if( *_ppOutBuffer )
	{
		*_ppOutBuffer	= new unsigned char[CSOFileSize];
		fseek( fp, 0, SEEK_SET );
		fread( *_ppOutBuffer, CSOFileSize, 1, fp );
	}
	if( *_pOutBufferSize )
	{
		*_pOutBufferSize	= CSOFileSize;
	}
	fclose( fp );

	return	NOERROR;
}

HRESULT	CreateVertexShaderFromCSO( ID3D11Device* _pDevice
								 , const char* _pFileName
								 , ID3D11VertexShader** _ppVertexShader
								 , ID3D11InputLayout** _ppInputLayout
								 , D3D11_INPUT_ELEMENT_DESC* _pInputElementDesc
								 , UINT _NumElements )
{
	HRESULT	hr;//実体

	//	ファイルを読み込む
	unsigned	char*	pCSOData;
	long	CSOFileSize;
	hr	= LoadCSOFromFile( _pFileName, &pCSOData, &CSOFileSize );
	if( FAILED( hr ) )
		return	hr;

	//	頂点シェーダーを作成する
	hr	= _pDevice->CreateVertexShader( pCSOData,
										CSOFileSize,
										nullptr,
										_ppVertexShader );
	_ASSERT_EXPR( SUCCEEDED( hr ), hr_trace( hr ) );
	if( FAILED( hr ) )
	{
		delete[]	pCSOData;
		pCSOData = nullptr;
		return	hr;	//	作成できなかったので初期化失敗
	}

	//	入力レイアウトを作成する
	hr	= _pDevice->CreateInputLayout( _pInputElementDesc
									 , _NumElements
									 , pCSOData
									 , CSOFileSize
									 , _ppInputLayout );
	_ASSERT_EXPR( SUCCEEDED( hr ), hr_trace( hr ) );

	delete[]	pCSOData;
	pCSOData = nullptr;
	return	hr;
}

HRESULT	CreatePixelShaderFromCSO( ID3D11Device* _pDevice
								, const char* _pFileName
								, ID3D11PixelShader** _ppPixelShader )
{
	HRESULT	hr;
	//	ファイルを読み込む
	unsigned	char*	pCSOData;
	long	CSOFileSize;
	hr	= LoadCSOFromFile( _pFileName, &pCSOData, &CSOFileSize );
	if( FAILED( hr ) )
		return	hr;

	//	ピクセルシェーダーを作成する
	hr	= _pDevice->CreatePixelShader( pCSOData
									 , CSOFileSize
									 , nullptr
									 , _ppPixelShader );
	_ASSERT_EXPR( SUCCEEDED( hr ), hr_trace( hr ) );

	delete[]	pCSOData;
	pCSOData = nullptr;
	return hr;
}




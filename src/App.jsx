import React from 'react';
import Header from './components/Header';
import BlogPostList from './components/BlogPostList';
import Footer from './components/Footer';
import { BlogProvider } from './context/BlogContext';

const App = () => {
  return (
    <BlogProvider>
      <div className="app">
        <Header />
        <BlogPostList />
        <Footer />
      </div>
    </BlogProvider>
  );
};

export default App;
